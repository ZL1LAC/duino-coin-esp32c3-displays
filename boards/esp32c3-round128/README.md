# ESP32-C3 1.28" Round Display — Duino-Coin Miner

Board-specific guide for the **ESP32-2424S012** (GC9A01 240×240 round, optional CST816D touch).

**Project home:** [README.md](../../README.md) · **Other boards:** [DISPLAYS.md](../../docs/DISPLAYS.md)

Mining firmware for the **ESP32-2424S012** board (ESP32-C3 + **GC9A01** 240×240 round IPS, ~37 mm).

Uses the **same mining UI as the Spotpear Mini TV** ([ST7735 128×128](../esp32c3-minitv/)), scaled for the round panel. See **[DISPLAYS.md](../../docs/DISPLAYS.md)** for a side-by-side comparison.

## What you need

- Arduino IDE 2.x
- Board: **ESP32C3 Dev Module**
- Library: **TFT_eSPI** (Bodmer)
- Duino-Coin account + 2.4 GHz WiFi

## Arduino IDE settings

| Setting | Value |
|---------|--------|
| Board | ESP32C3 Dev Module |
| USB CDC On Boot | **Enabled** |
| Partition Scheme | **Huge APP (3MB No OTA/1MB SPIFFS)** |
| Upload Speed | **115200** |
| Serial Monitor | **115200** baud |

## 1. Configure credentials

Edit `ESP_Code/Settings.h`:

```cpp
#define DISPLAY_GC9A01   // not DISPLAY_ST7735
```

Set `DUCO_USER`, `MINER_KEY`, `SSID`, `PASSWORD`.

## 2. Configure TFT_eSPI

Copy `GC9A01_setup.h` (this folder) → `Arduino/libraries/TFT_eSPI/User_Setups/Setup_ESP32_2424S012.h`

In `User_Setup_Select.h` (comment out other setups):

```cpp
#include <User_Setups/Setup_ESP32_2424S012.h>
```

Apply the ESP32-C3 SPI fix from [patches/TFT_eSPI/README.md](../../patches/TFT_eSPI/README.md) (required on core 3.x).

## 3. Upload

**Pre-built firmware:** [docs/FLASH.md](../../docs/FLASH.md) — use `esp32c3-round128-merged-flash.bin` from [GitHub Releases](https://github.com/ZL1LAC/duino-coin-boards/releases).

**From source:** open `ESP_Code/ESP_Code.ino`, upload, open Serial Monitor at **115200**, press **RESET**.

## Mining screen

Same rows as Spotpear Mini TV (wifi, hashrate, diff, shares, IP, uptime) — inset for the circular visible area.

### Touch

**CST816D** capacitive touch (model **2424S012C**). `CST816D.cpp` lives in `ESP_Code/` (Arduino compiles it with the sketch).

| Action | Effect |
|--------|--------|
| Tap | Rotate display |
| Swipe up / down | Brightness |

**Serial debug (115200):** on boot look for `Touch: I2C 0x15 OK`. When you tap, you should see `Touch: X=… Y=…`. If you see **MISSING**, the touch chip is not on the bus (wrong board variant or wiring). If OK but no X/Y lines when tapping, touch init failed. If X/Y appear but screen does not rotate, report that.

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
| Black screen | Correct TFT_eSPI setup; re-upload after library change |
| Boot crash `MTVAL: 0x10` | Apply ESP32-C3 `REG_SPI_BASE` patch |
| Upload fails | BOOT+RESET; 115200 baud; close Serial Monitor |
| Wrong board UI | Only one of `DISPLAY_ST7735` / `DISPLAY_GC9A01` in `Settings.h` |

## Other display

For the **Spotpear 1.44" Mini TV** (ST7735), use `DISPLAY_ST7735` and the [esp32c3-minitv](../esp32c3-minitv/) guide.

## Lopaka

UI layout import: [lopaka/drawScreen_mining_240_GC9A01.txt](lopaka/drawScreen_mining_240_GC9A01.txt) — see [docs/lopaka.md](../../docs/lopaka.md).
