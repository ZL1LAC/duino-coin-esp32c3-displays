# Pre-built firmware

Ready-to-flash **merged binaries** for supported boards. Built from `ESP_Code/` with the correct display profile and **WiFiManager captive portal** enabled so you can enter WiFi and Duino-Coin credentials after the first flash — no need to compile unless you want hard-coded settings in `Settings.h`.

## Latest downloads

Check **[GitHub Releases](https://github.com/ZL1LAC/duino-coin-boards/releases)** (tagged `firmware-v*`).

| Board | File | Guide |
|-------|------|--------|
| Spotpear ESP32-C3 Mini TV | `esp32c3-minitv-merged-flash.bin` | [boards/esp32c3-minitv](../boards/esp32c3-minitv/) |
| ESP32-2424S012 round | `esp32c3-round128-merged-flash.bin` | [boards/esp32c3-round128](../boards/esp32c3-round128/) |

Each release folder also includes `manifest.json` (build metadata) and `FLASH.txt` (quick command).

## First boot (release builds)

1. Flash the merged `.bin` (see [docs/FLASH.md](../docs/FLASH.md)).
2. Power on — the board creates a WiFi network named **`Duino-Coin`**.
3. Connect with phone/laptop, open the captive portal, enter:
   - Home WiFi SSID and password (2.4 GHz)
   - Duino-Coin username and mining key
4. The miner saves settings and reboots into normal mining.

To change credentials later, re-flash or build from source with your own `Settings.h` (without `CAPTIVE_PORTAL`).

## Build from source yourself

If you prefer your credentials compiled in, or you changed the code:

```bash
# Linux / macOS / WSL / Git Bash
bash scripts/build-firmware.sh all          # release-style (captive portal)
# or compile in Arduino IDE — see board README
```

Requires [arduino-cli](https://arduino.github.io/arduino-cli/) and Python 3 (`pip install esptool`).

Output lands in `firmware/dist/<board>/`.

## Publishing a new release (maintainer)

```bash
git tag firmware-v1.0.0
git push origin firmware-v1.0.0
```

GitHub Actions builds both board images and attaches them to the release.

Manual test build without tagging: **Actions → Firmware → Run workflow**.

## Why not commit `.bin` files to `main`?

Binaries are ~1.2 MB each and change every code edit. Releases keep the repo lean while still giving you a stable download URL.
