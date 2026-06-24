# Pre-built firmware

**No `Settings.h` file required.** Ready-to-flash **merged binaries** for supported boards. Built from `ESP_Code/` with the correct display profile and **WiFiManager captive portal** enabled so you can enter WiFi and Duino-Coin credentials after the first flash — no need to compile unless you want hard-coded settings in `Settings.h`.

## Latest downloads

Check **[GitHub Releases](https://github.com/ZL1LAC/duino-coin-boards/releases)** (tagged `firmware-v*`).

| Board | File | Guide |
|-------|------|--------|
| Spotpear ESP32-C3 Mini TV | `esp32c3-minitv-firmware.bin` | [devices/esp32c3-minitv](../devices/esp32c3-minitv/) |
| ESP32-2424S012 round | `esp32c3-round128-firmware.bin` | [devices/esp32c3-round128](../devices/esp32c3-round128/) |
| LilyGO T-Deck | `lilygo-t-deck-firmware.bin` | [devices/lilygo-t-deck](../devices/lilygo-t-deck/) |
| Heltec WiFi LoRa 32 (V2) | `heltec-wifi-lora-32-v2-firmware.bin` | [devices/heltec-wifi-lora-32-v2](../devices/heltec-wifi-lora-32-v2/) |
| LilyGO T-Deck Pro | `lilygo-t-deck-pro-firmware.bin` | [devices/lilygo-t-deck-pro](../devices/lilygo-t-deck-pro/) |
| LilyGO T-Beam v1.1 | `lilygo-t-beam-v11-firmware.bin` | [devices/lilygo-t-beam-v11](../devices/lilygo-t-beam-v11/) |

Each release also includes per-device `*-FLASH.txt` and `*-manifest.json`.

## First boot (release builds)

1. Flash the merged `.bin` (see [docs/FLASH.md](../docs/FLASH.md)).
2. Power on — the board creates a WiFi network named **`Duino-Coin`**.
3. Connect with phone/laptop, open the captive portal, enter:
   - Home WiFi SSID and password (2.4 GHz)
   - Duino-Coin username and mining key
4. The miner saves settings and reboots into normal mining.

To change credentials later, re-flash the release bin or build from source with `sync-device miner` and your own WiFi/user in `Settings.h` (without `CAPTIVE_PORTAL`).

To reproduce release-style builds locally: `bash scripts/build-firmware.sh <board>` or `sync-device.ps1 <id> miner-portal`.

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

Each device with `firmware.enabled: true` gets its own **`.bin`** attached to the GitHub Release (not source code):

```bash
git tag firmware-v1.0.8
git push origin firmware-v1.0.8   # must push the tag — triggers CI build + release upload
```

GitHub Actions compiles one `*-firmware.bin` per device and attaches them to the release page.

Manual test build without tagging: **Actions → Firmware → Run workflow**.

## Why not commit `.bin` files to `main`?

Binaries are ~1.2 MB each and change every code edit. Releases keep the repo lean while still giving you a stable download URL.