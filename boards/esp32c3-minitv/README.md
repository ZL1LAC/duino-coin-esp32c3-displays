# Duino-Coin on the Spotpear ESP32-C3 1.44" "Mini TV" (ST7735)

Board-specific guide for the **Spotpear 128×128 ST7735** panel.

**Project home:** [README.md](../../README.md) · **Other boards:** [DISPLAYS.md](../../docs/DISPLAYS.md)

This firmware is the official Duino-Coin `ESP_Code` fork, set up to mine on the
Spotpear ESP32-C3 1.44-inch LCD board and show live mining stats on the
128×128 ST7735 screen.

Copy `ESP_Code/Settings.h.example` → `ESP_Code/Settings.h` and add your Duino-Coin account and WiFi
(2.4 GHz only on ESP32-C3). Steps below cover Arduino IDE, libraries, TFT_eSPI,
and upload.

---

## 0. What was changed for this board

- `ESP_Code/Settings.h.example` – enable `#define DISPLAY_ST7735` (disable `DISPLAY_GC9A01`)
- `ESP_Code/DisplayHal.h` – 128×128 ST7735 mining UI
- `ST7735_setup.h` (this folder) / `patches/TFT_eSPI/Setup_Spotpear_ESP32C3_144.h` – TFT_eSPI pins

---

## 1. Install the Arduino IDE + ESP32 board support

1. Install the **Arduino IDE 2.x** (https://www.arduino.cc/en/software).
2. Open **File ▸ Preferences**. In *Additional boards manager URLs* add:
   ```
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```
3. Open **Tools ▸ Board ▸ Boards Manager**, search **esp32**, and install
   **"esp32" by Espressif Systems** (v3.x is fine).

---

## 2. Install the required libraries

Open **Tools ▸ Manage Libraries** and install:

| Library | Author | Why |
| --- | --- | --- |
| **ArduinoJson** | Benoit Blanchon | Parsing the mining node info |
| **TFT_eSPI** | Bodmer | Drives the ST7735 screen |

(The ESP32 core already provides WiFi, HTTPClient, ArduinoOTA, mDNS, Ticker.)

---

## 3. Point TFT_eSPI at this board (the important step)

TFT_eSPI does **not** read pin settings from the sketch — it reads them from its
own setup file. You have to tell it to use this board's pins (in `ST7735_setup.h`).
Pick **one** method.

### Method A — paste into TFT_eSPI's `User_Setup.h` (simplest)

1. Find the TFT_eSPI library folder:
   - Windows: `Documents\Arduino\libraries\TFT_eSPI\`
   - macOS: `~/Documents/Arduino/libraries/TFT_eSPI/`
2. Open **`User_Setup.h`** in that folder.
3. Delete (or comment out) its entire contents and **paste in the contents of
   `boards/esp32c3-minitv/ST7735_setup.h`**. Save.

That's it — TFT_eSPI now uses GPIO3/4/2/0/5 for this board.

> If you use TFT_eSPI for other projects too and don't want to overwrite
> `User_Setup.h`, use Method B instead.

### Method B — add it as a selectable setup

1. Copy `ST7735_setup.h` from this folder into the TFT_eSPI library folder
   (next to `User_Setup.h`), renamed to e.g.
   `User_Setups/Setup_Spotpear_C3_144.h`.
2. Open **`User_Setup_Select.h`** in the TFT_eSPI folder.
3. Comment out the existing active `#include` line (usually
   `#include <User_Setup.h>`) and add:
   ```cpp
   #include <User_Setups/Setup_Spotpear_C3_144.h>
   ```
4. Save.

---

## 4. Board settings in Arduino IDE

Open the **Tools** menu and set (values from the board's documentation):

| Setting | Value |
| --- | --- |
| Board | **ESP32C3 Dev Module** (under "ESP32 Arduino") |
| USB CDC On Boot | **Enabled** |
| CPU Frequency | 160 MHz |
| Flash Frequency | 80 MHz |
| Flash Mode | QIO |
| Flash Size | 4 MB (32 Mb) |
| Partition Scheme | **Huge APP (3 MB No OTA/1 MB SPIFFS)** — sketch is ~1.2 MB |
| Upload Speed | **115200** (use 921600 only if uploads are reliable) |
| JTAG Adapter | Integrated USB JTAG |
| Port | the COM/tty port that appears when you plug the board in |

> **USB CDC On Boot = Enabled** matters: this board's USB is wired straight to the
> ESP32-C3, so serial output only works with CDC on.

---

## 5. Open, compile, upload

**Pre-built firmware:** [docs/FLASH.md](../../docs/FLASH.md) — flash `esp32c3-minitv-merged-flash.bin` from [GitHub Releases](https://github.com/ZL1LAC/duino-coin-boards/releases) if you don't want to compile.

**From source:**

1. Open **`ESP_Code/ESP_Code.ino`** (the IDE will open the whole sketch folder,
   including `Settings.h`, `DisplayHal.h`, etc. as tabs).
2. Plug the board in via USB.
3. Click **Upload** (the → arrow).

If upload fails to start, hold the **BOOT** button, tap **RESET**, release BOOT,
and upload again (puts the C3 into download mode).

On success you'll see, in order: a boot info screen → "Duino-Coin / Waiting for
WiFi…" → "Waiting for node…" → the live mining screen.

---

## 6. Using it

- Open **Tools ▸ Serial Monitor** at **115200 baud** to watch logs (hashrate,
  accepted shares, etc.). After upload, press the board **RESET** button once if
  you see no output.
- Track earnings in your wallet or at https://wallet.duinocoin.com
- **BOOT button** rotates the screen 90° each press, so you can mount the board
  in any orientation.
- Expected hashrate for a single-core ESP32-C3 is roughly **16–18 kH/s**.

---

## 7. If nothing happens / “not loading”

**Upload stuck or fails**

1. Tools → Port — pick the COM port that appears when you plug the board in.
2. Tools → Upload Speed → **115200**.
3. Tools → Partition Scheme → **Huge APP (3MB No OTA/1MB SPIFFS)**.
4. Hold **BOOT**, tap **RESET**, release **BOOT**, then click Upload.

**Board runs but Serial Monitor is blank**

1. Tools → USB CDC On Boot → **Enabled**.
2. Serial Monitor baud → **115200** (not 500000).
3. Press **RESET** after opening Serial Monitor.

**Screen stays black but serial shows `Duino-Coin 4.3`**

- WiFi may be failing (ESP32-C3 needs a **2.4 GHz** network). Serial will show
  `Connecting to: …` then dots, or `WiFi timeout — retrying`.

**Crash right after `Duino-Coin 4.3` (`Store access fault`, `MTVAL: 0x10`)**

- TFT_eSPI `REG_SPI_BASE` patch required — see note below.

## 8. If the screen looks wrong

> **Crash right after `Duino-Coin 4.3` (`Store access fault`, `MTVAL: 0x10`)?**  
> This is a known TFT_eSPI + ESP32-C3 + Arduino core 3.x bug. In  
> `Documents\Arduino\libraries\TFT_eSPI\Processors\TFT_eSPI_ESP32_C3.h`, the  
> `REG_SPI_BASE` fix must use `#undef REG_SPI_BASE` before redefining it (the stock  
> `#ifndef` guard is ineffective once ESP-IDF headers load). That patch should already  
> be on your machine if setup was run from this project.

Open `ST7735_setup.h` and see the troubleshooting notes at the bottom:

- **Coloured border / image shifted a few px** → try a different `ST7735_*TAB*`
  define (e.g. swap `ST7735_GREENTAB128` for `ST7735_BLACKTAB` or
  `ST7735_REDTAB`).
- **Red and blue swapped** → change `TFT_BGR` to `TFT_RGB`.
- **Mirrored / upside down** → just press the BOOT button to rotate.

After editing `ST7735_setup.h`, re-copy it into TFT_eSPI (Method A/B) and re-upload.

---

## 9. If you ever want to turn the screen off

In `ESP_Code/Settings.h`, comment out the line:
```cpp
#define DISPLAY_ST7735
```
…and re-upload. The board will mine headless.

## Lopaka

UI layout import: [lopaka/drawScreen_mining_128_ST7735.txt](lopaka/drawScreen_mining_128_ST7735.txt) — see [docs/lopaka.md](../../docs/lopaka.md).
