# Heltec WiFi LoRa 32 (V2)

Board-specific guide for the **[Heltec WiFi LoRa 32 (V2)](https://heltec.org/project/wifi-lora-32v2/)** — classic ESP32 + SX1276/SX1278 LoRa, onboard **0.96" 128×64 SSD1306 OLED**.

**Project home:** [README.md](../../README.md) · **Testbench:** [testbench/heltec-wifi-lora-32-v2/](../../testbench/heltec-wifi-lora-32-v2/)

> **Status:** testbench bring-up — generic OLED test first, then full miner. LoRa radio is not used by the miner.

---

## Hardware

| Item | Value |
|------|--------|
| MCU | ESP32 (dual-core, 8 MB flash) |
| Display | SSD1306 OLED, 128×64 (I²C) |
| LoRa | SX1276 / SX1278 (not used by miner) |
| USB | CP2102 serial |
| LED | GPIO **25** |
| BOOT | GPIO **0** |

### OLED pins (dedicated bus — not the header I²C on 21/22)

| Signal | GPIO |
|--------|------|
| SDA | **4** |
| SCL | **15** |
| RST | **16** |
| Vext (display power) | **21** — drive **LOW** to turn OLED rail **on** |

Reserved for OLED / LoRa (avoid in your own wiring): 4, 5, 12–16, 18–19, 21, 26–27, 34–35.

Open GPIO examples: 2, 13, 17, 22, 23, 32, 33, 36–39.

---

## Quick test (generic sketch)

1. Copy `testbench/heltec-wifi-lora-32-v2/TestConfig.h.example` → `TestConfig.h`
2. Sync:
   ```powershell
   .\scripts\sync-testbench-test.ps1 heltec-wifi-lora-32-v2
   ```
3. **No TFT_eSPI step** — this board uses U8g2 for the OLED.
4. Install library: **U8g2** by olikraus (Arduino Library Manager).
5. Open **`testbench/GenericTest/GenericTest.ino`**, upload with board settings below.
6. Serial Monitor **115200** — striped OLED pattern + board name; `tick N` on serial.

When that looks good, move to the full miner via `Settings.h` + `sync-testbench-settings.ps1` → `ESP_Code/ESP_Code.ino`.

---

## Settings.h

Enable both defines (testbench profile does this for you):

```cpp
#define DISPLAY_SSD1306
#define HELTEC_WIFI_LORA_32_V2   // Vext + OLED I2C pins in HeltecDisplay.h
```

---

## Arduino IDE

| Setting | Value |
|---------|--------|
| Board | **WiFi LoRa 32(V2)** (Heltec ESP32 series) |
| Partition Scheme | **Huge APP (3 MB)** or default |
| Upload Speed | 921600 (or 115200 if upload fails) |
| Serial Monitor | **115200** |

**CI / arduino-cli FQBN:** `esp32:esp32:heltec_wifi_lora_32_V2:UploadSpeed=921600,PartitionScheme=huge_app`

---

## Libraries

| Library | Purpose |
|---------|---------|
| [U8g2](https://github.com/olikraus/u8g2) | SSD1306 OLED (required) |

No TFT_eSPI configuration for this board.

---

## Troubleshooting

| Symptom | Fix |
|---------|-----|
| Blank OLED, serial OK | Run `sync-testbench-test.ps1 heltec-wifi-lora-32-v2` — old T-Deck `TestConfig.h` will break this board |
| Blank OLED after sync | Board must be **WiFi LoRa 32(V2)** in Arduino IDE (not generic ESP32 Dev) |
| Garbled display | Uses U8g2 **SW I2C** on GPIO 15/4 — do not use default `Wire.begin()` without pins |
| Wrong pins | V2 uses SDA=4, SCL=15 — **not** header I²C 21/22 |
| Upload fails | Hold BOOT, tap RESET; try 115200 upload speed |
| Mining OK, no display | `Settings.h` must have `DISPLAY_SSD1306` + `HELTEC_WIFI_LORA_32_V2` |

---

## Checklist

See [docs/ADDING_A_BOARD.md](../../docs/ADDING_A_BOARD.md).
