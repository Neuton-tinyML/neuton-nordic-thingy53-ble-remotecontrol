"""
Gesture-controlled Spotify remote — PC-side bridge.

A Thingy:53 recognizes gestures on-device and sends one BLE notification each.
This script turns those into Spotify commands and pushes live state to a browser
dashboard.

    Thingy:53 --BLE--> spotify_bridge.py --HTTPS--> Spotify Web API
                              |
                              +--ws://localhost:8765--> spotify_dashboard.html

This module is the single source of truth; the dashboard only renders what it
receives. Data path:

    BLE notification -> BLEManager._handle_payload -> asyncio.Queue
        -> Bridge.gesture_worker -> Bridge.handle_gesture -> Spotify
        -> Bridge.broadcast -> dashboard

Firmware behaviours that shape this code (see ../src/main.c):
  * IDLE and UNKNOWN are filtered out before notifying; we ignore them anyway.
  * Gestures are debounced ~800 ms EXCEPT the rotations, which are meant to be
    repetitive and stream at full inference rate — hence the volume coalescing.

Environment:
  * Native Windows or Linux, not WSL (no Bluetooth adapter access there).
  * Spotify Premium, and an already-active playback session — the Web API cannot
    start Spotify from closed.

Usage:
    pip install bleak websockets spotipy
    set SPOTIPY_CLIENT_ID / SPOTIPY_CLIENT_SECRET   (see README_spotify.md)
    python spotify_bridge.py
"""

import asyncio
import contextlib
import json
import os
import signal
import sys
import time
from enum import Enum, auto

from bleak import BleakClient, BleakScanner

import spotipy
from spotipy.oauth2 import SpotifyOAuth

try:
    from websockets.asyncio.server import serve as ws_serve  # websockets >= 14
except ImportError:  # pragma: no cover
    from websockets import serve as ws_serve


# ============================================================================
# Credentials file
# ============================================================================


def load_env_file(path):
    """Load KEY=VALUE lines from `path` into os.environ. True if the file existed.

    Saves having to export SPOTIPY_CLIENT_ID/SECRET in every new shell. Hand-
    rolled rather than pulling in python-dotenv, since it is a dozen lines and
    keeps the dependency list to the three the README already names.

    The real environment always wins, so an export can still override the file
    for a one-off run.
    """
    try:
        with open(path, encoding="utf-8") as handle:
            lines = handle.readlines()
    except OSError:
        return False

    for raw in lines:
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        # Tolerate lines pasted from a shell script.
        if line.startswith("export "):
            line = line[len("export "):].lstrip()

        key, sep, value = line.partition("=")
        if not sep:
            continue
        key, value = key.strip(), value.strip()
        # Strip one matching pair of surrounding quotes.
        if len(value) >= 2 and value[0] == value[-1] and value[0] in "\"'":
            value = value[1:-1]
        if key and key not in os.environ:
            os.environ[key] = value
    return True


def example_file_looks_filled_in(path):
    """True if the .env.example template holds real values instead of placeholders.

    Editing the template instead of copying it to .env is an easy mistake, and
    the symptom — credentials silently not found — gives no hint as to why. It
    also risks committing the secret, since the template is not git-ignored.
    """
    try:
        text = open(path, encoding="utf-8").read()
    except OSError:
        return False

    for line in text.splitlines():
        line = line.strip()
        if line.startswith("#") or "=" not in line:
            continue
        key, _, value = line.partition("=")
        if key.strip() not in ("SPOTIPY_CLIENT_ID", "SPOTIPY_CLIENT_SECRET"):
            continue
        value = value.strip().strip("\"'")
        if value and "your_" not in value and "_here" not in value:
            return True
    return False


# Must run before the config below, which reads the environment at import time.
ENV_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), ".env")
EXAMPLE_FILE = ENV_FILE + ".example"
ENV_FILE_LOADED = load_env_file(ENV_FILE)


# ============================================================================
# Configuration
# ============================================================================

# Must match the firmware or the scan never finds the device.
BLE_DEVICE_NAME = "Neuton NRF RemoteControl"
BLE_CHAR_UUID = "516a51c4-b1e1-47fa-8327-8acaeb3399eb"

WS_HOST = "localhost"
WS_PORT = 8765

# Every command needs "user-modify-playback-state". Widening this list requires
# deleting the cached token so the user is re-prompted.
SPOTIFY_SCOPE = (
    "user-read-playback-state "
    "user-modify-playback-state "
    "user-read-currently-playing"
)

# Must match the redirect URI registered in the Spotify developer dashboard.
# Nothing listens on it, so the page fails to load and spotipy asks you to paste
# the URL instead — that is expected.
SPOTIFY_REDIRECT_URI = os.environ.get(
    "SPOTIPY_REDIRECT_URI", "http://127.0.0.1:8888/callback"
)

# Cached token, so only the first run is interactive. Git-ignored: it grants
# account access.
SPOTIFY_CACHE_PATH = os.path.join(
    os.path.dirname(os.path.abspath(__file__)), ".spotify_token_cache"
)

VOLUME_STEP = 10
# Used when unmuting with no remembered level (e.g. bridge restarted muted).
UNMUTE_FALLBACK_VOLUME = 50
# Quiet period before sending a volume change, so a burst of rotations becomes
# one API call.
VOLUME_COALESCE_S = 0.25
# Duplicate guard for one-shot gestures. Firmware already enforces ~800 ms, so
# keep this well below that to avoid swallowing deliberate repeats.
ACTION_COOLDOWN_S = 0.5
# Makes the dashboard notice changes made elsewhere (phone, track ending).
POLL_INTERVAL_S = 2.0
# Under WSL the BlueZ call hangs instead of reporting a missing adapter, which
# would leave the user on "Scanning..." forever.
SCAN_TIMEOUT_S = 12.0


# ============================================================================
# Gesture definitions
# ============================================================================


class Gestures(Enum):
    """Gesture classes, mirroring class_label_t in the firmware.

    The firmware enum is 0-indexed (CLASS_LABEL_IDLE = 0) and transmits that raw
    value, so decoding is always `Gestures(wire_value + 1)`. The offset matches
    uiapp_ble.py; changing it here without changing the firmware silently maps
    every gesture to the wrong action.
    """

    IDLE = 1
    UNKNOWN = 2
    SWIPE_RIGHT = 3
    SWIPE_LEFT = 4
    DOUBLE_SHAKE = 5
    DOUBLE_THUMB = 6
    ROTATION_RIGHT = 7
    ROTATION_LEFT = 8


# Sent to the dashboard and used as its icon lookup key, so renaming one here
# means renaming it in GESTURE_ICONS in spotify_dashboard.html too.
gestures_string_names = {
    Gestures.UNKNOWN: "UNKNOWN GESTURE",
    Gestures.SWIPE_RIGHT: "SWIPE RIGHT",
    Gestures.SWIPE_LEFT: "SWIPE LEFT",
    Gestures.DOUBLE_SHAKE: "DOUBLE SHAKE",
    Gestures.DOUBLE_THUMB: "DOUBLE THUMB",
    Gestures.ROTATION_RIGHT: "ROTATION RIGHT",
    Gestures.ROTATION_LEFT: "ROTATION LEFT",
    Gestures.IDLE: "NO MOVEMENTS",
}

IGNORED_GESTURES = (Gestures.IDLE, Gestures.UNKNOWN)


# ============================================================================
# BLE state machine
# ============================================================================


class BLEState(Enum):
    SCANNING = auto()
    CONNECTING = auto()
    LISTENING = auto()


BLEState_to_str = {
    BLEState.SCANNING: "SCANNING",
    BLEState.CONNECTING: "CONNECTING",
    BLEState.LISTENING: "LISTENING",
}


class BLEManager:
    """Owns the BLE link: scan -> connect -> listen, reconnecting forever.

    Gestures are pushed onto a queue rather than acted on inline, so a slow
    Spotify call cannot stall reception of the notifications behind it. State
    machine shape follows uiapp_ble.py, which is proven against this firmware.
    """

    def __init__(self, device_name, characteristic_uuid, queue, on_change):
        self.device_name = device_name
        self.char_uuid = characteristic_uuid
        self.queue = queue
        # Called with no arguments when state or last_error changes; the Bridge
        # reads the current values back off this object.
        self.on_change = on_change

        self._state = BLEState.SCANNING
        self._last_error = None
        self.device = None
        self.client = None
        self.disconnect_event = asyncio.Event()

    # Properties so assignment notifies the dashboard; the != guard avoids
    # spamming the socket every scan cycle.

    @property
    def state(self):
        return self._state

    @state.setter
    def state(self, value):
        if value != self._state:
            self._state = value
            self.on_change()

    @property
    def last_error(self):
        return self._last_error

    @last_error.setter
    def last_error(self, value):
        if value != self._last_error:
            self._last_error = value
            self.on_change()

    @property
    def state_str(self):
        return BLEState_to_str[self._state]

    def on_disconnect(self, client):
        """Called by bleak on link loss. Must be sync, so it only sets a flag."""
        print("BLE -> Device disconnected, restarting scan")
        self.disconnect_event.set()

    async def scan(self):
        print("BLE -> Scanning...")
        try:
            devices = await asyncio.wait_for(
                BleakScanner.discover(), timeout=SCAN_TIMEOUT_S
            )
        except asyncio.TimeoutError:
            self.last_error = (
                "BLE scan timed out. If this is WSL, there is no Bluetooth "
                "adapter access — run this on native Windows."
            )
            print(f"BLE -> {self.last_error}")
            return
        except Exception as exc:
            self.last_error = f"BLE scan failed: {exc}"
            print(f"BLE -> {self.last_error}")
            await asyncio.sleep(2)
            return

        # Scan worked, so clear any stale adapter error even if not found.
        self.last_error = None

        for device in devices:
            # Substring match tolerates truncated/padded advertised names.
            if device.name and (
                device.name == self.device_name or device.name in self.device_name
            ):
                print(f"BLE -> Found {device.name}")
                self.device = device
                self.state = BLEState.CONNECTING
                return

        await asyncio.sleep(2)

    async def connect(self):
        print(f"BLE -> Connecting to {self.device.name}")
        # A disconnect from a previous session may have left this set.
        self.disconnect_event.clear()

        self.client = BleakClient(
            self.device, disconnected_callback=self.on_disconnect
        )
        try:
            await self.client.connect()
            print("BLE -> Connected")
            self.last_error = None
            # Let GATT services finish setting up before subscribing.
            await asyncio.sleep(1)
            self.state = BLEState.LISTENING
        except Exception as exc:
            self.last_error = f"BLE connection failed: {exc}"
            print(f"BLE -> {self.last_error}")
            self.state = BLEState.SCANNING

    def _handle_payload(self, data):
        """Decode one notification and queue the gesture.

        Wire format is "<class_index>,<probability>", e.g. b"2,95" for
        SWIPE_RIGHT at 95%, built by snprintf("%d,%d") in the firmware.

        Must never raise: an exception here propagates into bleak's callback
        machinery and can kill notifications for the rest of the session.
        """
        try:
            ble_str = data.decode("utf-8").strip()
            predicted_class_str, probability_str = ble_str.split(",")
            gesture = Gestures(int(predicted_class_str) + 1)
            probability = int(probability_str.strip())
        except (UnicodeDecodeError, ValueError) as exc:
            # Covers bad bytes, wrong field count, non-numerics, and an index
            # outside the enum.
            print(f"BLE -> Ignoring malformed payload {data!r}: {exc}")
            return

        print(f"{gestures_string_names[gesture]}, probability {probability} %")
        if gesture in IGNORED_GESTURES:
            return

        try:
            self.queue.put_nowait((gesture, probability, time.monotonic()))
        except asyncio.QueueFull:
            # Drop the oldest: responding to the latest movement feels correct,
            # replaying a stale backlog feels broken.
            with contextlib.suppress(asyncio.QueueEmpty):
                self.queue.get_nowait()
            with contextlib.suppress(asyncio.QueueFull):
                self.queue.put_nowait((gesture, probability, time.monotonic()))

    async def listen(self):
        """Subscribe to notifications and block until the device disconnects."""
        characteristic = None
        for service in self.client.services:
            for char in service.characteristics:
                if char.uuid == self.char_uuid:
                    characteristic = char
                    break

        if not characteristic:
            # Right name, wrong GATT profile — most likely older firmware.
            print("BLE -> Characteristic not found")
            with contextlib.suppress(Exception):
                await self.client.disconnect()
            self.state = BLEState.SCANNING
            return

        loop = asyncio.get_running_loop()

        def notification_handler(sender, data):
            # Some backends (WinRT) call this off the event loop thread.
            loop.call_soon_threadsafe(self._handle_payload, data)

        await self.client.start_notify(characteristic.uuid, notification_handler)
        print("BLE -> Listening")

        await self.disconnect_event.wait()

        # Both calls usually fail if the device vanished, which is the common
        # case — hence the suppression.
        print("BLE -> Stopping notifications")
        with contextlib.suppress(Exception):
            await self.client.stop_notify(characteristic.uuid)
        with contextlib.suppress(Exception):
            await self.client.disconnect()

        self.state = BLEState.SCANNING

    async def run(self):
        self.on_change()  # Publish initial state.
        while True:
            if self.state == BLEState.SCANNING:
                await self.scan()
            elif self.state == BLEState.CONNECTING:
                await self.connect()
            elif self.state == BLEState.LISTENING:
                await self.listen()

    async def shutdown(self):
        """Disconnect cleanly, or the device keeps thinking it is connected."""
        if self.client is not None and self.client.is_connected:
            print("BLE -> Disconnecting")
            with contextlib.suppress(Exception):
                await self.client.disconnect()


# ============================================================================
# Spotify control
# ============================================================================


class SpotifyController:
    """Async-friendly wrapper around the blocking spotipy client.

    spotipy uses `requests`, so every call goes to a worker thread to keep the
    event loop free. A lock serializes them because the client is not
    thread-safe and refreshes its OAuth token lazily.
    """

    def __init__(self):
        # SpotifyOAuth reads SPOTIPY_CLIENT_ID/SECRET from the environment.
        auth_manager = SpotifyOAuth(
            scope=SPOTIFY_SCOPE,
            redirect_uri=SPOTIFY_REDIRECT_URI,
            cache_path=SPOTIFY_CACHE_PATH,
            open_browser=True,
        )
        # Timeout matters: a hung request would hold the lock indefinitely.
        self._sp = spotipy.Spotify(auth_manager=auth_manager, requests_timeout=10)
        self._lock = asyncio.Lock()

    async def _call(self, fn, *args, **kwargs):
        async with self._lock:
            return await asyncio.to_thread(fn, *args, **kwargs)

    async def current_playback(self):
        """Full playback state, or None when no device is active."""
        return await self._call(self._sp.current_playback)

    async def next_track(self):
        await self._call(self._sp.next_track)

    async def previous_track(self):
        await self._call(self._sp.previous_track)

    async def pause(self):
        await self._call(self._sp.pause_playback)

    async def play(self):
        await self._call(self._sp.start_playback)

    async def set_volume(self, percent):
        await self._call(self._sp.volume, percent)

    async def me(self):
        return await self._call(self._sp.me)


def spotify_error_text(exc):
    """Spotify's human-readable message, minus the URL prefix spotipy adds.

    spotipy builds msg as "<url>:\\n <message>", so the tail is the useful part.
    """
    msg = getattr(exc, "msg", "") or ""
    return msg.split(":\n", 1)[-1].strip()


def is_volume_refusal(exc):
    """True when a command failed because the device cannot do volume.

    Checks the message text as well as `reason`, because the two are populated
    independently: observed 403s carry "Cannot control device volume" while
    `reason` is often absent. Relying on `reason` alone misses the real case.
    """
    reason = (getattr(exc, "reason", None) or "").upper()
    if reason in ("VOLUME_CONTROL_DISALLOW", "DEVICE_NOT_CONTROLLABLE"):
        return True
    return "cannot control device volume" in spotify_error_text(exc).lower()


def disallowed_actions(playback):
    """Playback actions Spotify currently forbids, as a set of names.

    Spotify gates individual actions by context, independently of subscription —
    this is why a Premium account still gets a 403.

    Two response shapes exist and their booleans mean OPPOSITE things, so they
    get separate branches; merging them would invert every check:
      * {"actions": {"disallows": {"toggling_shuffle": true}}}  true => forbidden
      * {"actions": {"pausing": false}}                        false => forbidden
    """
    actions = playback.get("actions") or {}

    disallows = actions.get("disallows")
    if isinstance(disallows, dict):
        return {name for name, flag in disallows.items() if flag}

    # Allow-flag form. Ignore non-booleans so a nested object cannot be misread.
    return {
        name
        for name, flag in actions.items()
        if name != "disallows" and flag is False
    }


def summarize_playback(playback):
    """Reduce Spotify's playback object to the fields the dashboard draws.

    Fields are defensively defaulted — Spotify nulls parts of this structure for
    podcasts, local files, private sessions and devices without volume — and
    both branches return the same keys so the dashboard can render blindly.
    """
    if not playback:
        return {
            "active": False,
            "is_playing": False,
            "track": None,
            "artists": None,
            "album": None,
            "art": None,
            "progress_ms": 0,
            "duration_ms": 0,
            "volume": None,
            "shuffle": False,
            "device": None,
            "device_type": None,
            "supports_volume": None,
            "is_restricted": False,
            "disallowed": [],
        }

    # `or {}` not `.get(k, {})`: these keys can be present but null.
    item = playback.get("item") or {}
    album = item.get("album") or {}
    images = album.get("images") or []
    device = playback.get("device") or {}

    return {
        "active": True,
        "is_playing": bool(playback.get("is_playing")),
        "track": item.get("name"),
        "artists": ", ".join(a["name"] for a in item.get("artists") or []) or None,
        "album": album.get("name"),
        "art": images[0]["url"] if images else None,  # Largest first.
        "progress_ms": playback.get("progress_ms") or 0,
        "duration_ms": item.get("duration_ms") or 0,
        "volume": device.get("volume_percent"),
        # Informational only — double shake mutes rather than toggling shuffle.
        "shuffle": bool(playback.get("shuffle_state")),
        "device": device.get("name"),
        "device_type": device.get("type"),
        # False => cannot be volume-controlled at all. None => field absent, so
        # unknown, and we still try rather than refusing pre-emptively.
        "supports_volume": device.get("supports_volume"),
        "is_restricted": bool(device.get("is_restricted")),
        "disallowed": sorted(disallowed_actions(playback)),
    }


# ============================================================================
# Bridge
# ============================================================================


class Bridge:
    """Consumes gestures, drives Spotify, and owns all shared state.

    Runs three concurrent tasks (see `run`): the BLE state machine, the gesture
    worker, and the playback poller. All on one event loop, so the attributes
    below need no locking.
    """

    def __init__(self):
        # Bounded: rotations can outpace the API, and an unbounded queue would
        # act on gestures long after the user made them.
        self.queue = asyncio.Queue(maxsize=16)
        self.clients = set()

        self.spotify = None
        self.ble = None

        # Mirrored to the dashboard.
        self.ble_state = "STARTING"
        self.ble_error = None
        self.gesture = None
        self.action = None
        self.error = None
        self.playback = summarize_playback(None)
        self.user = None

        self._last_action_at = {}      # Gesture -> last accepted, for cooldown.
        self._pending_volume = None    # Requested but not yet sent.
        self._volume_task = None
        self._last_caps = None         # So capabilities log only on change.
        self._volume_before_mute = None
        # Device that already refused volume. Rotations stream continuously, so
        # without this every burst fires another doomed request and risks a 429.
        # Learned at runtime because some devices refuse without advertising
        # supports_volume=false. Cleared when the active device changes.
        self._volume_blocked_device = None

    # ---- state broadcast --------------------------------------------------

    def snapshot(self):
        """The complete state message; the dashboard holds no state of its own."""
        # Derived rather than stored, so it cannot disagree with the volume shown.
        playback = dict(self.playback)
        playback["muted"] = playback.get("volume") == 0

        return {
            "type": "state",
            "ble": self.ble_state,
            "gesture": self.gesture,
            "action": self.action,
            # A BLE problem outranks a Spotify one: without a link nothing works.
            "error": self.ble_error or self.error,
            "spotify": playback,
            "user": self.user,
            # Lets the dashboard smooth the progress bar between polls.
            "server_time": time.time(),
        }

    def broadcast(self):
        """Fire-and-forget push to every dashboard; never blocks the caller."""
        if not self.clients:
            return
        payload = json.dumps(self.snapshot())
        for ws in list(self.clients):  # Copy: _send can mutate the set.
            asyncio.create_task(self._send(ws, payload))

    async def _send(self, ws, payload):
        try:
            await ws.send(payload)
        except Exception:
            self.clients.discard(ws)

    async def ws_handler(self, websocket, *_):
        """Serve one dashboard. `*_` absorbs the legacy `path` argument."""
        self.clients.add(websocket)
        peer = getattr(websocket, "remote_address", None)
        print(f"WS -> Dashboard connected ({peer}), {len(self.clients)} client(s)")
        try:
            # Immediately, or a dashboard opened between polls renders empty.
            await websocket.send(json.dumps(self.snapshot()))
            # Iterating detects the client going away; the dashboard never sends.
            async for _message in websocket:
                pass
        except Exception:
            pass  # A closing tab surfaces as an exception. Normal.
        finally:
            self.clients.discard(websocket)
            print(f"WS -> Dashboard disconnected, {len(self.clients)} client(s)")

    def on_ble_change(self):
        self.ble_state = self.ble.state_str
        self.ble_error = self.ble.last_error
        self.broadcast()

    # ---- gesture handling -------------------------------------------------

    def _cooldown_blocked(self, gesture, now):
        """True if this gesture fired too recently. Records the time otherwise."""
        last = self._last_action_at.get(gesture)
        if last is not None and (now - last) < ACTION_COOLDOWN_S:
            return True
        self._last_action_at[gesture] = now
        return False

    async def gesture_worker(self):
        """Consume gestures one at a time, surviving every API failure.

        Serial by design: concurrent commands would fight over playback state.
        If this task dies the remote goes silent with no obvious cause, hence
        the broad handling.
        """
        while True:
            gesture, probability, _received_at = await self.queue.get()

            # Recorded before acting, so the dashboard shows what was recognized
            # even when the command then fails.
            self.gesture = {
                "name": gestures_string_names[gesture],
                "probability": probability,
                "ts": time.time(),  # Lets the dashboard spot a NEW gesture.
            }

            try:
                await self.handle_gesture(gesture)
            except spotipy.SpotifyException as exc:
                self._report_spotify_error(
                    exc, what=gestures_string_names[gesture].title()
                )
            except Exception as exc:
                self.error = f"{type(exc).__name__}: {exc}"
                print(f"Spotify -> Error: {self.error}")

            self.broadcast()

    def _report_spotify_error(self, exc, what=None):
        """Turn a SpotifyException into something actionable.

        Spotify's `reason` code and message are populated independently and
        neither is always present, so both are reported. This replaced code that
        assumed every 403 meant "not Premium", which actively misled: volume is
        refused on Premium accounts all the time for device reasons.

        `what` names the attempted action, so the banner says what failed.
        """
        reason = getattr(exc, "reason", None)  # Absent on older spotipy.
        prefix = f"{what}: " if what else ""
        text = spotify_error_text(exc)

        if exc.http_status == 404 or reason == "NO_ACTIVE_DEVICE":
            self.error = (
                f"{prefix}no active Spotify device. Start playback on your "
                "phone or the desktop app, then try again."
            )
        elif reason == "PREMIUM_REQUIRED":
            self.error = f"{prefix}Spotify Premium is required for playback control."
        elif is_volume_refusal(exc):
            self.error = (
                f"{prefix}this device does not accept volume control via the "
                "Spotify Web API. Switch playback to the Spotify desktop app "
                "or web player, which do."
            )
        elif exc.http_status == 403:
            # Other restriction, e.g. "Restriction violated". Quote Spotify
            # verbatim; guessing between these is what caused the old message.
            detail = " / ".join(d for d in (text, reason) if d) or "no reason given"
            self.error = (
                f"{prefix}Spotify refused this command ({detail}). The action "
                "is not allowed for what is currently playing or for this "
                "device — the account plan is not necessarily the problem."
            )
        elif exc.http_status == 429:
            self.error = "Rate limited by Spotify (429). Slow down the gestures."
        else:
            self.error = f"{prefix}Spotify error {exc.http_status}: {exc.msg}"

        print(f"Spotify -> {self.error}")
        print(f"Spotify ->   raw: {exc}")  # Status, code and reason.

    async def handle_gesture(self, gesture):
        """Perform the Spotify action for one gesture.

        Exceptions propagate to gesture_worker. The optimistic local updates let
        the toggles work: waiting for a poll to confirm would make a rapid
        second gesture repeat the first instead of reversing it.
        """
        now = time.monotonic()

        # Rotations bypass the cooldown — the firmware sends them continuously by
        # design, and coalescing is what turns that into smooth volume control.
        if gesture in (Gestures.ROTATION_RIGHT, Gestures.ROTATION_LEFT):
            step = VOLUME_STEP if gesture == Gestures.ROTATION_RIGHT else -VOLUME_STEP
            self._nudge_volume(step)
            return

        if self._cooldown_blocked(gesture, now):
            print(f"Bridge -> Ignoring repeat {gestures_string_names[gesture]}")
            return

        if gesture == Gestures.SWIPE_RIGHT:
            self.error = None
            await self.spotify.next_track()
            self.action = "Next track"
            # Spotify does not report the new track instantly.
            await asyncio.sleep(0.3)
            await self.refresh_playback()

        elif gesture == Gestures.SWIPE_LEFT:
            self.error = None
            await self.spotify.previous_track()
            self.action = "Previous track"
            await asyncio.sleep(0.3)
            await self.refresh_playback()

        elif gesture == Gestures.DOUBLE_THUMB:
            self.error = None
            if self.playback.get("is_playing"):
                await self.spotify.pause()
                self.action = "Pause"
                self.playback["is_playing"] = False
            else:
                await self.spotify.play()
                self.action = "Play"
                self.playback["is_playing"] = True

        elif gesture == Gestures.DOUBLE_SHAKE:
            self._toggle_mute()

        print(f"Bridge -> {self.action}")

    # ---- volume and mute --------------------------------------------------

    def _volume_blocked_reason(self):
        """Why volume cannot work right now, or None if it can.

        Shared by rotation and mute, since mute is a volume change and both hit
        the same device restrictions.
        """
        device_name = self.playback.get("device") or "This device"

        if self._volume_blocked_device is not None and (
            self._volume_blocked_device == self.playback.get("device")
        ):
            return (
                f"{device_name} refused volume control, so further volume "
                "gestures are ignored. Switch playback to the Spotify desktop "
                "app or web player to control volume."
            )

        # `is False`, not falsy: None means unknown and should still be tried.
        if self.playback.get("supports_volume") is False:
            return (
                f"{device_name} does not support volume control via the "
                "Spotify Web API. Switch playback to the desktop app or web "
                "player, which do."
            )

        if self.playback.get("is_restricted"):
            return (
                f"Spotify marks {device_name} as restricted, so it cannot be "
                "remote-controlled. Try the desktop app or web player."
            )

        return None

    def _current_volume(self):
        """Volume to base a change on — the pending target if one is in flight.

        Using the pending value is what makes rotation deltas accumulate;
        otherwise every rotation in a burst computes the same "observed + 10".
        """
        if self._pending_volume is not None:
            return self._pending_volume
        return self.playback.get("volume")

    def _apply_volume(self, target, label, what="Volume"):
        """Queue an absolute volume, deferring the API call.

        All volume changes funnel through here so the guards, the optimistic
        update and the coalescing timer apply uniformly.
        """
        blocked = self._volume_blocked_reason()
        if blocked:
            self.error = f"{what}: {blocked}"
            print(f"Spotify -> {self.error}")
            return False

        self._pending_volume = max(0, min(100, target))  # Spotify rejects <0/>100.
        self.playback["volume"] = self._pending_volume   # Feel instant.
        self.action = label
        self.error = None

        # Only if none pending — that is the coalescing. Later gestures just
        # change the target this task will send.
        if self._volume_task is None or self._volume_task.done():
            self._volume_task = asyncio.create_task(self._flush_volume())
        return True

    def _nudge_volume(self, step):
        """Change volume by a relative step."""
        blocked = self._volume_blocked_reason()
        if blocked:
            self.error = f"Volume: {blocked}"
            print(f"Spotify -> {self.error}")
            return

        base = self._current_volume()
        if base is None:
            device_name = self.playback.get("device") or "This device"
            self.error = (
                f"Volume: {device_name} does not report a volume level, so "
                "there is nothing to adjust."
            )
            print(f"Spotify -> {self.error}")
            return

        self._apply_volume(base + step, f"Volume {max(0, min(100, base + step))}")

    def _toggle_mute(self):
        """Mute or unmute, remembering the level to restore.

        The Web API has no mute endpoint, so this is "volume 0" plus "put the
        old level back". Consequently mute inherits every volume restriction: on
        a device that refuses volume control it cannot work either. The
        remembered level is process-local, so a restart while muted loses it.
        """
        blocked = self._volume_blocked_reason()
        if blocked:
            self.error = f"Mute: {blocked}"
            print(f"Spotify -> {self.error}")
            return

        current = self._current_volume()
        if current is None:
            device_name = self.playback.get("device") or "This device"
            self.error = (
                f"Mute: {device_name} does not report a volume level, so it "
                "cannot be muted."
            )
            print(f"Spotify -> {self.error}")
            return

        if current > 0:
            self._volume_before_mute = current
            self._apply_volume(0, f"Muted (was {current})", what="Mute")
        else:
            restore = self._volume_before_mute or UNMUTE_FALLBACK_VOLUME
            self._volume_before_mute = None
            self._apply_volume(restore, f"Unmuted ({restore})", what="Unmute")

    async def _flush_volume(self):
        """After the quiet period, send the accumulated volume once."""
        await asyncio.sleep(VOLUME_COALESCE_S)

        # Clearing marks "nothing in flight", so refresh_playback stops
        # overriding polls and the next gesture starts from fresh state.
        target, self._pending_volume = self._pending_volume, None
        if target is None:
            return

        # Handled here, not propagated: this is its own task, so an escaping
        # exception would only become an unretrieved-exception warning.
        try:
            self.error = None
            await self.spotify.set_volume(target)
            print(f"Bridge -> Volume {target}")
        except spotipy.SpotifyException as exc:
            self._report_spotify_error(exc, what="Volume")
            # Remember the refusal so streaming rotations stop retrying. Done
            # here because only this call site knows it was a volume command.
            if is_volume_refusal(exc):
                self._volume_blocked_device = self.playback.get("device")
                print(
                    "Bridge -> Volume control disabled for "
                    f"{self._volume_blocked_device!r} until the device changes"
                )
        except Exception as exc:
            self.error = f"{type(exc).__name__}: {exc}"
            print(f"Spotify -> Error: {self.error}")

        self.broadcast()

    # ---- playback polling -------------------------------------------------

    async def refresh_playback(self):
        """Re-read playback state and store the summary."""
        playback = await self.spotify.current_playback()
        summary = summarize_playback(playback)

        # A volume change in flight means Spotify is reporting the old value;
        # keep showing the target so the dial does not snap backwards.
        if self._pending_volume is not None:
            summary["volume"] = self._pending_volume

        # A new device may well accept volume, so give it a chance.
        if (
            self._volume_blocked_device is not None
            and summary["device"] != self._volume_blocked_device
        ):
            print(
                f"Bridge -> Device changed to {summary['device']!r}, "
                "re-enabling volume control"
            )
            self._volume_blocked_device = None

        self.playback = summary
        self._log_capabilities(summary)
        return summary

    def _log_capabilities(self, summary):
        """Log what the device/context permits, on change.

        "Gesture recognized, nothing happened" is otherwise hard to diagnose:
        the cause is usually a restriction invisible without these flags.
        """
        if not summary["active"]:
            caps = "no active device"
        else:
            caps = (
                f"device={summary['device']!r} type={summary['device_type']} "
                f"supports_volume={summary['supports_volume']} "
                f"restricted={summary['is_restricted']} "
                f"disallowed={summary['disallowed'] or 'none'}"
            )
        if caps != self._last_caps:
            self._last_caps = caps
            print(f"Spotify -> Capabilities: {caps}")

    async def poll_loop(self):
        """Refresh forever, so changes made elsewhere become visible."""
        while True:
            try:
                await self.refresh_playback()
                # Playback is live again, so drop a stale "no active device".
                if self.error and self.playback["active"]:
                    self.error = None
                self.broadcast()
            except spotipy.SpotifyException as exc:
                self._report_spotify_error(exc)
                self.broadcast()
            except Exception as exc:
                # Log only: a banner would flicker, and the next poll likely works.
                print(f"Spotify -> Poll failed: {type(exc).__name__}: {exc}")
            await asyncio.sleep(POLL_INTERVAL_S)

    # ---- lifecycle --------------------------------------------------------

    async def run(self):
        """Authenticate, bind the server, then run the three tasks forever."""
        # Spotify first: it is the step most likely to need the user, and its
        # failure is fatal. Better to fail before the device connects.
        print("Spotify -> Authenticating (a browser window may open)...")
        self.spotify = SpotifyController()
        try:
            # me() also proves the token works; spotipy builds the client lazily.
            me = await self.spotify.me()
            self.user = me.get("display_name") or me.get("id")
            print(f"Spotify -> Authenticated as {self.user}")
            # Otherwise the symptom is every command failing with an opaque 403.
            if me.get("product") != "premium":
                print(
                    "Spotify -> WARNING: account is not Premium; playback "
                    "control endpoints will be rejected."
                )
        except Exception as exc:
            print(f"Spotify -> Authentication failed: {exc}")
            raise

        self.ble = BLEManager(
            BLE_DEVICE_NAME, BLE_CHAR_UUID, self.queue, self.on_ble_change
        )

        try:
            server_ctx = await ws_serve(self.ws_handler, WS_HOST, WS_PORT)
        except OSError as exc:
            print(
                f"WS -> Cannot bind {WS_HOST}:{WS_PORT} ({exc}).\n"
                "     Another spotify_bridge.py is probably still running in "
                "another terminal — stop it first."
            )
            raise

        print(f"WS -> Dashboard server on ws://{WS_HOST}:{WS_PORT}")
        print("Open spotify_dashboard.html in a browser.")

        # gather propagates the first exception, so an unexpected failure brings
        # the bridge down rather than leaving it half-working.
        async with server_ctx:
            await asyncio.gather(
                self.ble.run(),
                self.gesture_worker(),
                self.poll_loop(),
            )

    async def shutdown(self):
        if self.ble is not None:
            await self.ble.shutdown()
        for ws in list(self.clients):
            with contextlib.suppress(Exception):
                await ws.close()


# ============================================================================
# Main
# ============================================================================


async def main():
    """Check credentials, wire up signals, run the bridge. Returns an exit code."""
    # Checked here because spotipy's own failure is a confusing stack trace, and
    # exporting these in the wrong shell is a common first-run mistake.
    if ENV_FILE_LOADED:
        print(f"Loaded settings from {os.path.basename(ENV_FILE)}")

    if not os.environ.get("SPOTIPY_CLIENT_ID") or not os.environ.get(
        "SPOTIPY_CLIENT_SECRET"
    ):
        # Deliberately the bare filename, not the full path: this output tends to
        # get pasted into chats and screenshots, and an absolute path leaks the
        # user's home directory.
        if example_file_looks_filled_in(EXAMPLE_FILE):
            print(
                "Your credentials appear to be in .env.example, but the file\n"
                "that is actually read is .env — copy .env.example to .env.\n"
                "\n"
                "Do this promptly: .env.example is NOT git-ignored, so a secret\n"
                "left there can be committed. .env is git-ignored.\n"
            )
        print(
            "Missing Spotify credentials.\n"
            "\n"
            "Easiest fix — create a file named .env next to this script,\n"
            "containing:\n"
            "    SPOTIPY_CLIENT_ID=your_client_id\n"
            "    SPOTIPY_CLIENT_SECRET=your_client_secret\n"
            "(copy .env.example to .env and fill it in; .env is git-ignored)\n"
            "\n"
            "Or export SPOTIPY_CLIENT_ID and SPOTIPY_CLIENT_SECRET in this\n"
            f"shell. SPOTIPY_REDIRECT_URI is optional ({SPOTIFY_REDIRECT_URI}).\n"
            "See README_spotify.md for how to create the Spotify app."
        )
        return 1

    bridge = Bridge()
    # A task, not a bare await, so the signal handler can cancel it.
    runner = asyncio.ensure_future(bridge.run())

    loop = asyncio.get_running_loop()
    for sig in (signal.SIGINT, signal.SIGTERM):
        with contextlib.suppress(NotImplementedError, AttributeError):
            # Windows loops lack add_signal_handler and SIGTERM is not
            # universal; the KeyboardInterrupt handler below covers Windows.
            loop.add_signal_handler(sig, runner.cancel)

    try:
        await runner
    except (asyncio.CancelledError, KeyboardInterrupt):
        print("\nShutting down...")
    except Exception as exc:
        # Startup failures; the specific cause was already printed.
        print(f"Fatal: {type(exc).__name__}: {exc}")
        await bridge.shutdown()
        return 1

    await bridge.shutdown()  # Always release the device.
    return 0


if __name__ == "__main__":
    try:
        sys.exit(asyncio.run(main()) or 0)
    except KeyboardInterrupt:
        # On Windows Ctrl+C arrives here rather than at the signal handler.
        print("\nInterrupted")
        sys.exit(0)
 