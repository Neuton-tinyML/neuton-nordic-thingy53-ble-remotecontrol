# How to run python UI demo

There are two front ends for the same firmware:

- **[uiapp_ble.py](uiapp_ble.py)** (below) — visualizes the recognized gesture.
- **[spotify_bridge.py](spotify_bridge.py)** — drives real Spotify playback with
  the gestures (skip, play/pause, volume, mute) and renders live "now playing" state in a browser dashboard. See
  [README_spotify.md](README_spotify.md).

## Gesture visualization demo

1. Install requirements `pip install -r requirements.txt`.
2. Turn on Nordic Thingy-53 device by switching the toggle to on position.
3. Run python script for BLE connection handling and demo visualization [uiapp_ble.py](uiapp_ble.py) using `python uiapp_ble.py` command.
4. The UI will open in the new window and after approx 10 seconds you can start doing gestures with the device and UI will reflect the detected class in real time.
5. Console output will also show the recognized class and its probability.