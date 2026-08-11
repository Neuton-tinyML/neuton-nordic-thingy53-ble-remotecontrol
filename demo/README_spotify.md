# Gesture-controlled Spotify remote

Control real Spotify playback with gestures from the Thingy:53. The device runs
the on-device gesture model and streams the recognized class over a custom BLE
GATT characteristic; `spotify_bridge.py` on the PC turns those into Spotify Web
API calls and pushes live state to a browser dashboard.

```
Thingy:53 (BLE, custom GATT)
   -> spotify_bridge.py    (bleak + spotipy + websockets)
        -> Spotify Web API  (play/pause/skip/volume/mute)
        -> ws://localhost:8765
              -> spotify_dashboard.html  (renders live "now playing" state)
```

`spotify_bridge.py` is the single source of truth: it owns the BLE connection,
calls Spotify, and broadcasts JSON state. The dashboard is a pure renderer.

This is an alternative front end to [uiapp_ble.py](uiapp_ble.py), which shows the
raw gesture classification instead of driving Spotify. Both consume the same
firmware and the same characteristic.

## Gesture mapping

| Gesture | Action |
|---|---|
| Swipe right | Next track |
| Swipe left | Previous track |
| Double thumb | Play / pause toggle |
| Rotation right | Volume +10 |
| Rotation left | Volume −10 |
| Double shake | Mute / unmute |
| Idle / unknown | No action |

## Requirements

- **Spotify Premium.** The playback-control endpoints (play, pause, skip,
  volume) are Premium-only. A free account can read state but every command
  comes back `403`. Note that Premium is *not* sufficient on its own — see
  [Why volume and mute can fail on Premium](#why-volume-and-mute-can-fail-on-premium).
- **Native Windows or Linux — not WSL.** WSL has no Bluetooth adapter access, so
  `bleak` cannot scan. The bridge bounds the scan at 12 s and tells you this
  rather than hanging forever.
- Python 3.11+.

## Setup

### 1. Install dependencies

```bash
pip install bleak websockets spotipy
```

(or `pip install -r requirements.txt` / `uv sync` for the full demo set)

### 2. Create a Spotify app

1. Go to https://developer.spotify.com/dashboard and create an app.
2. Add exactly this redirect URI: `http://127.0.0.1:8888/callback`
3. Copy the Client ID and Client Secret.

### 3. Save the credentials

Create a file named `.env` in this directory — copy the provided template:

```bash
cp .env.example .env      # Linux / macOS
copy .env.example .env    # Windows
```

Then fill it in:

```
SPOTIPY_CLIENT_ID=your_client_id
SPOTIPY_CLIENT_SECRET=your_client_secret
```

`.env` is git-ignored, so the secret stays out of the repository. This is a
one-time step — the bridge reads it on every run, so there is nothing to
re-enter. `SPOTIPY_REDIRECT_URI` is optional and defaults to
`http://127.0.0.1:8888/callback`.

<details>
<summary>Alternatives to a <code>.env</code> file</summary>

**Per-shell export.** Anything already set in the environment overrides `.env`,
which is handy for a one-off run with a different app:

```powershell
$env:SPOTIPY_CLIENT_ID    = "your_client_id"      # PowerShell
$env:SPOTIPY_CLIENT_SECRET = "your_client_secret"
```

```bash
export SPOTIPY_CLIENT_ID=your_client_id           # Linux / macOS
export SPOTIPY_CLIENT_SECRET=your_client_secret
```

**Persistent Windows user variables.** Survives reboots, no file needed, but
applies to every process you run — reopen the terminal afterwards:

```bat
setx SPOTIPY_CLIENT_ID "your_client_id"
setx SPOTIPY_CLIENT_SECRET "your_client_secret"
```

</details>

## Running

1. **Start playing something on Spotify** (phone, desktop app, or web player).
   The Web API can only control an *existing* playback session — it cannot
   launch Spotify from a fully closed state. This is the single most common
   cause of "nothing happens".
2. Turn on the Thingy:53.
3. Start the bridge:

   ```bash
   python spotify_bridge.py
   ```

4. On first run a browser opens for OAuth. After you approve, you are
   redirected to `http://127.0.0.1:8888/callback`, which **will not load** —
   nothing is listening there. That is expected: copy the full URL from the
   address bar and paste it into the terminal when spotipy prompts. The token is
   then cached in `.spotify_token_cache` and later runs are non-interactive.
5. Open [spotify_dashboard.html](spotify_dashboard.html) in a browser. It works
   even before the bridge is up — it retries the WebSocket every 2 s.
6. Wait for the console to print `BLE -> Listening`, then start gesturing.

## Dashboard

Shows the current track with album art, a progress bar, volume, mute state,
the active Spotify device, the last recognized gesture with its confidence, and
a running activity log. Connection status for both the bridge and BLE is in the
header; problems appear as banners across the top, which clear after about 5 s
and stack up to three at once. A persistent fault (a BLE problem, which the
bridge keeps re-sending) stays up until it is resolved.

## Troubleshooting

| Symptom | Cause / fix |
|---|---|
| `Missing Spotify credentials` | No `.env` file, or it is missing a value. See step 3. |
| Banner: "No active Spotify device" | Nothing is playing. Start playback somewhere first (see step 1). |
| Volume tile shows "(locked)" | The active device does not accept volume over the Web API. Move playback to the desktop app or web player. |
| Muted tile shows "(locked)" | Mute uses the volume endpoint, so the same device restriction applies. |
| Only rotation / double shake fail | Not a Premium problem — see [below](#why-volume-and-mute-can-fail-on-premium). |
| Banner mentions `403` | Read the reason code in the message and the `Capabilities:` line in the console. |
| `BLE scan timed out ... run this on native Windows` | You are in WSL. There is no adapter to use. |
| `OSError: only one usage of each socket address` | An old `spotify_bridge.py` still holds port 8765. Stop it first. |
| Dashboard stuck on "bridge offline" | Bridge not running, or it failed before the WebSocket bound — check the console. |
| Dashboard looks stale after you edited the HTML | Browsers cache local files hard. Hard-refresh with Ctrl+F5. |
| Volume jumps in big steps | Expected. Rotation gestures are not debounced in firmware, so the bridge coalesces them into one API call every 250 ms. |

## Why volume and mute can fail on Premium

If skip and play/pause work but **rotation (volume) and double shake (mute)
come back `403`**, your account is fine — those working commands need exactly
the same Premium entitlement. Both failing gestures use the volume endpoint,
which is gated separately:

- **Volume** depends on the *device*. Spotify reports `supports_volume` for the
  active device, and many cannot be volume-controlled remotely: phones, some
  Connect speakers, Chromecast and AirPlay targets. The desktop app and web
  player generally can. A device can also be flagged `is_restricted`, which
  blocks remote control more broadly.
- **Mute** is not a separate endpoint at all. The Web API has no mute, so
  double shake sets the volume to 0 and restores the previous level on the next
  shake. That means mute inherits the volume restriction above: on a device that
  refuses volume control, mute cannot work either.

The bridge reads both signals up front and refuses locally, with a specific
explanation, rather than firing a doomed request — and marks the affected tile
"(locked)" on the dashboard.

Those advertised flags are not always populated, though. Devices are observed
refusing volume with `403 Player command failed: Cannot control device volume`
while *not* reporting `supports_volume: false`. Two consequences:

- The failure is matched on Spotify's message text as well as the `reason` code,
  because `reason` is frequently absent (`None`) on exactly these errors.
- The first refusal is remembered for that device, so streaming rotation
  gestures stop retrying. Otherwise every rotation burst would fire another
  doomed request every 250 ms and risk a `429` rate limit. The block clears
  automatically when playback moves to a different device.

To see what your current device and context allow, watch the console:

```
Spotify -> Capabilities: device='My iPhone' type=smartphone supports_volume=False restricted=False disallowed=[]
```

That line is printed at startup and whenever the capabilities change. In the
example above, volume and mute would both be refused (iPhones do not accept
remote volume control) — transferring playback to the Spotify desktop app or web
player fixes both.

## Implementation notes

Two firmware behaviours drive the bridge's design — see
[src/main.c](../src/main.c):

- The firmware **never sends** `IDLE` or `UNKNOWN`; it filters them before
  notifying. The bridge ignores them anyway if they ever arrive.
- The firmware applies an 800 ms debounce to every gesture **except**
  `ROTATION_RIGHT` / `ROTATION_LEFT`, which are meant to be repetitive and so
  stream at inference rate. Applying `volume ±10` per notification would slam
  0→100 and hammer the API, so the bridge accumulates the deltas and issues at
  most one `volume` call per `VOLUME_COALESCE_S` (250 ms). The dashboard is
  updated optimistically so it still feels instant.

Other details:

- Gestures are queued (`asyncio.Queue`, max 16) rather than acted on inside the
  BLE callback, so a slow HTTP call can never stall notifications. On overflow
  the oldest is dropped — a live remote beats replaying a stale backlog.
- spotipy is blocking, so every call runs in a worker thread behind a lock.
- Playback is re-polled every 2 s, so changes made elsewhere (skipping on your
  phone) show up on the dashboard.
- The BLE layer reuses the scan → connect → listen state machine from
  `uiapp_ble.py`, reconnecting automatically when the device drops.

## Tuning

Constants at the top of [spotify_bridge.py](spotify_bridge.py):

| Constant | Default | Meaning |
|---|---|---|
| `VOLUME_STEP` | 10 | Volume change per rotation gesture |
| `UNMUTE_FALLBACK_VOLUME` | 50 | Level restored when unmuting with no remembered level |
| `VOLUME_COALESCE_S` | 0.25 | Window for merging rotation gestures |
| `ACTION_COOLDOWN_S` | 0.5 | Duplicate suppression for one-shot gestures |
| `POLL_INTERVAL_S` | 2.0 | Playback state refresh interval |
| `SCAN_TIMEOUT_S` | 12.0 | Hard bound on a BLE scan |
| `WS_PORT` | 8765 | Dashboard WebSocket port |

`BLE_DEVICE_NAME` and `BLE_CHAR_UUID` must stay in sync with the firmware.
