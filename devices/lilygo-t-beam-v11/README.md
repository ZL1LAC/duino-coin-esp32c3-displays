# LilyGO T-Beam v1.1

Board-specific guide for the **[LilyGO T-Beam v1.1](https://github.com/Xinyuan-LilyGO/TTGO-T-Beam)** — ESP32 + SX1276/1278 LoRa, u-blox GPS, optional **0.96" SSD1306 OLED** on the I²C header, AXP192 PMU.

**Project home:** [README.md](../../README.md) · **Pin map:** [LilyGo LoRa series docs](https://github.com/Xinyuan-LilyGO/LilyGo-LoRa-Series/blob/master/docs/en/t_beam/t_beam_hw.md)

> **Note:** v1.1 uses **AXP192** (not AXP2101 on newer T-Beam boards). OLED must be soldered to the I²C pads (SDA/SCL). LoRa and GPS are not used by the miner.

---

## Hardware

| Item | Value |
|------|--------|
| MCU | ESP32 (dual-core, 4 MB flash typical) |
| Display | SSD1306 OLED 128×64 (I²C **0x3C**) — optional module on header |
| PMU | AXP192 — **DCDC1** powers OLED |
| LoRa | SX1276 / SX1278 (not used by miner) |
| GPS | u-blox NEO-6M/8 (not used by miner) |
| USB | CP2102 serial |
| User button | GPIO **38** |

### I²C (OLED + AXP192)

| Signal | GPIO |
|--------|------|
| SDA | **21** |
| SCL | **22** |

---

## Quick test (generic sketch)

1. Solder a **GND / 3V3 / SCL / SDA** OLED (SSD1306 128×64) if not already fitted.
2. Copy `TestConfig.h.example` → `TestConfig.h`
3. ```powershell
   .\scripts\sync-device.ps1 lilygo-t-beam-v11 test
   ```
4. Install library: **U8g2** by olikraus (Arduino Library Manager)
5. Open **`testbench/GenericTest/GenericTest.ino`**, upload with board settings below.
6. Serial Monitor **115200** — striped OLED + `tick N` on serial.

When that looks good, use captive portal (recommended) or hard-coded WiFi:

```powershell
# Recommended — no WiFi/username in source; first boot opens AP "Duino-Coin"
.\scripts\sync-device.ps1 lilygo-t-beam-v11 miner-portal

# Or hard-code credentials in Settings.h.example first, then:
.\scripts\sync-device.ps1 lilygo-t-beam-v11 miner
```

Then open **`ESP_Code/ESP_Code.ino`** and upload.

---

## Settings.h

```cpp
#define DISPLAY_SSD1306
#define LILYGO_T_BEAM_V11   // AXP192 + I2C 21/22 in TBeamDisplay.h
```

---

## Arduino IDE

| Setting | Value |
|---------|--------|
| Board | **TTGO T-Beam** (under ESP32 Arduino) |
| Upload Speed | 921600 (or 115200 if upload fails) |
| Serial Monitor | **115200** |

**CI / arduino-cli FQBN:** `esp32:esp32:ttgo-t-beam:UploadSpeed=921600`

---

## Libraries

| Library | Purpose |
|---------|---------|
| [U8g2](https://github.com/olikraus/u8g2) | SSD1306 OLED |

AXP192 power-on is built into `TBeamDisplay.h` (no extra library).

No TFT_eSPI configuration.

---

## Troubleshooting

| Symptom | Fix |
|---------|-----|
| Blank OLED, serial OK | Run `sync-device.ps1 lilygo-t-beam-v11 test`; check OLED wiring to **21/22/3V3/GND** |
| I²C / AXP init fails on serial | Try power cycle; some boards need OLED powered before AXP talks — see [Paxcounter T-Beam note](https://cyberman54.github.io/ESP32-Paxcounter/display-led/) |
| Wrong board revision | **v1.1 = AXP192**. v1.2+ may use AXP2101 — different PMU code |
| Upload fails | Hold **PRG** (GPIO 0), tap reset; try 115200 |
| Mining OK, no display | `Settings.h` needs `DISPLAY_SSD1306` + `LILYGO_T_BEAM_V11` |
| Boot screen frozen, no mining UI | Reflash latest code — mining updates re-bind I²C on core 0 after boot. Check Serial Monitor for WiFi/node messages || Stuck on boot, never mines | With `CAPTIVE_PORTAL`, phone joins Wi‑Fi **Duino-Coin** → captive page → enter home WiFi + Duino username. OLED shows **Join Duino-Coin WiFi** during setup |
| Reconfigure WiFi later | Visit `http://<miner-ip>/reset` (needs `WEB_DASHBOARD`) or erase flash / reflash with portal enabled |

---

## Battery

The onboard **18650** cell is monitored through the **AXP192** PMU (same I²C bus as the OLED). The mining screen shows a small battery icon in the **bottom-right**:

- **Battery connected** — fill level + **%** (bolt while charging from USB)
- **No battery (USB only)** — empty outline with an **X**

---

## Pre-built firmware

Pre-built **`lilygo-t-beam-v11-firmware.bin`** on [GitHub Releases](https://github.com/ZL1LAC/duino-coin-boards/releases) (tag `firmware-v*`).
