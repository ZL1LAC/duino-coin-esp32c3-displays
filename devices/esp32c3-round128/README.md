# ESP32-C3 1.28" Round Display — Duino-Coin Miner

Board-specific guide for the **ESP32-2424S012** (GC9A01 240×240 round, optional CST816D touch).

**Project home:** [README.md](../../README.md) · **Docs:** [DISPLAYS.md](../../docs/DISPLAYS.md)

> **Testbench:** active development — pre-built firmware is paused (`firmware.enabled: false` in [registry.json](../registry.json)) until new features ship. Build from source below.

Mining firmware for the **ESP32-2424S012** board (ESP32-C3 + **GC9A01** 240×240 round IPS, ~37 mm).

## Quick start (no compile)

**No `Settings.h` needed** — flash `esp32c3-round128-firmware.bin` from [GitHub Releases](https://github.com/ZL1LAC/duino-coin-boards/releases), then join WiFi **`Duino-Coin`** and use the captive portal. See [docs/FLASH.md](../../docs/FLASH.md).

## Build from source

Uses the **same mining UI as the Spotpear Mini TV** ([ST7735 128×128](../esp32c3-minitv/)), scaled for the round panel. See **[DISPLAYS.md](../../docs/DISPLAYS.md)** for a side-by-side comparison.

```powershell
# Miner (captive portal — no WiFi in Settings.h)
.\scripts\sync-device.ps1 esp32c3-round128 miner-portal
.\scripts\setup-tft-espi.ps1 esp32c3-round128
# Open ESP_Code/ESP_Code.ino, upload, Serial 115200

# Display-only bring-up (optional)
.\scripts\sync-device.ps1 esp32c3-round128 test
# Open testbench/GenericTest/GenericTest.ino
```

When features are ready for release, set `firmware.enabled: true` in [registry.json](../registry.json) and tag `firmware-v*`.

## What you need

- Arduino IDE 2.x
- Board: **ESP32C3 Dev Module**
- Library: **TFT_eSPI** (Bodmer)
- Duino-Coin account + 2.4 GHz WiFi

## Arduino IDE settings

> **Sketch too big / 101% of program storage?** Your **Partition Scheme** is wrong.
> The compiler limit `1310720` bytes (~1.25 MB) means **Default** partition — not Huge APP.
> Set **Tools → Partition Scheme → Huge APP (3MB No OTA/1MB SPIFFS)** and compile again.

| Setting | Value |
|---------|--------|
| Board | ESP32C3 Dev Module |
| USB CDC On Boot | **Enabled** |
| Flash Size | **4MB (32Mb)** |
| Partition Scheme | **Huge APP (3MB No OTA/1MB SPIFFS)** — sketch is ~1.3 MB with touch + captive portal |
| Upload Speed | **115200** |
| Serial Monitor | **115200** baud |

## 1. Configure credentials

`copy Settings.h.example Settings.h` in this folder, edit, then `.\scripts\sync-device.ps1 esp32c3-round128 miner`.

In `Settings.h`:

```cpp
#define DISPLAY_GC9A01   // not DISPLAY_ST7735
```

Set `DUCO_USER`, `MINER_KEY`, `SSID`, `PASSWORD`.

## 2. Configure TFT_eSPI

Copy `tft_setup.h` (this folder) → `Arduino/libraries/TFT_eSPI/User_Setups/Setup_ESP32_2424S012.h`

In `User_Setup_Select.h` (comment out other setups):

```cpp
#include <User_Setups/Setup_ESP32_2424S012.h>
```

Apply the ESP32-C3 SPI fix from [patches/TFT_eSPI/README.md](../../patches/TFT_eSPI/README.md) (required on core 3.x).

## 3. Upload

**Pre-built firmware:** [docs/FLASH.md](../../docs/FLASH.md) — use `esp32c3-round128-firmware.bin` from [GitHub Releases](https://github.com/ZL1LAC/duino-coin-boards/releases).

**From source:** open `ESP_Code/ESP_Code.ino`, upload, open Serial Monitor at **115200**, press **RESET**.

## Mining screen

Same rows as Spotpear Mini TV (wifi, hashrate, diff, shares, IP, uptime) — inset for the circular visible area.

### Touch

**CST816D** capacitive touch (model **2424S012C**). `CST816D.cpp` lives in `ESP_Code/` (Arduino compiles it with the sketch).

| Action | Effect |
|--------|--------|
| Tap | Rotate display; **wake** when screen is blank |
| Double-tap | Blank screen (backlight off) |
| Long press | Toggle backlight dim / bright |
| Swipe up / down | Brightness ± (cyan bar overlay) |
| Swipe left | **Stats** page (user, rig, WiFi, node, key) |
| Swipe right | **Mining** page |

Brightness and rotation persist across reboot (`Preferences`).

Serial debug (115200): gesture lines when active.

Disable touch: comment out `#define TOUCH_CST816D` in `ESP_Code/Settings.h`.

## Hardware

- **Model:** ESP32-2424S012 (back of PCB)
- **MCU:** ESP32-C3-MINI-1U
- **Display:** GC9A01, 240×240 round
- **USB:** TYPE-C (programming)
- **BOOT:** GPIO9 — cycles rotation
- **Backlight:** GPIO3 (set in firmware)

## Troubleshooting

| Problem | Fix |
|---------|-----|
| **Sketch too big** / `text section exceeds available space` / max `1310720` bytes | **Tools → Partition Scheme → Huge APP (3MB No OTA/1MB SPIFFS)** |
| Black screen | Correct TFT_eSPI setup; re-upload after library change |
| Boot crash `MTVAL: 0x10` | Apply ESP32-C3 `REG_SPI_BASE` patch |
| Upload fails | BOOT+RESET; 115200 baud; close Serial Monitor |
| Wrong board UI | Only one of `DISPLAY_ST7735` / `DISPLAY_GC9A01` in `Settings.h` |

## Other display

For the **Spotpear 1.44" Mini TV** (ST7735), use `DISPLAY_ST7735` and the [esp32c3-minitv](../esp32c3-minitv/) guide.

## Lopaka

UI layout import: [lopaka/drawScreen_mining_240_GC9A01.txt](lopaka/drawScreen_mining_240_GC9A01.txt) — see [docs/lopaka.md](../../docs/lopaka.md).