# Adding a new board

Step-by-step for porting Duino-Coin to new hardware. Use this when the board arrives — you do not need every step on day one.

**Quick scaffold:** `bash scripts/new-board.sh <board-id> "<Board Name>"`

---

## 1. Gather hardware info

Before coding, write down:

| Item | Your board |
|------|------------|
| MCU (ESP32-C3, S3, 8266, …) | |
| Display controller + size | |
| Touch (if any) + I2C pins | |
| SPI / I2C pin map | |
| BOOT / reset / backlight GPIO | |
| USB (CDC serial?) | |
| Flash size / partition needs | |

Photos of PCB silkscreen, factory demo repo, or AliExpress listing ID help later.

---

## 2. Create the board folder

```bash
bash scripts/new-board.sh my-new-board "My New Board Name"
```

This creates `boards/my-new-board/` from [`boards/_template/`](../boards/_template/) with:

- `README.md` — fill in Arduino IDE settings, pins, troubleshooting
- `tft_setup.h` — TFT_eSPI pin/driver template (skip if headless / OLED-only)

---

## 3. Firmware (`ESP_Code/`)

Depends on what the board needs:

| Need | Where |
|------|--------|
| New display driver / UI | `DisplayHal.h` — add `#if defined(DISPLAY_*)` block |
| Touch, sensors, etc. | New `.cpp`/`.h` in `ESP_Code/` |
| Enable in config | `Settings.h.example` — new `#define DISPLAY_*` |
| Mining loop hooks | `ESP_Code.ino`, `MiningJob.h` if input polling |

Copy patterns from existing blocks:

- **128×128 ST7735** → `DISPLAY_ST7735` in `DisplayHal.h`
- **240×240 GC9A01 + touch** → `DISPLAY_GC9A01`, `CST816D.cpp`

Headless board (no display): may only need pin/LED fixes in `Settings.h.example` — no `DisplayHal.h` changes.

---

## 3b. Local testbench (recommended)

**Phase 1 — generic test** (display + serial, no mining):

1. `testbench/<board-id>/TestConfig.h.example` → `TestConfig.h`
2. `scripts/sync-testbench-test.ps1 <board-id>` (or `.sh`)
3. Apply `tft_setup.h` to TFT_eSPI, open **`testbench/GenericTest/GenericTest.ino`**, upload.

**Phase 2 — full miner** when the screen works:

1. Edit `testbench/<board-id>/Settings.h` (credentials + display `#define`s).
2. Run `scripts/sync-testbench-settings.ps1 <board-id>` (or `.sh`).
3. Upload **`ESP_Code/ESP_Code.ino`**.

See [testbench/README.md](../testbench/README.md).

---

## 4. Register the board

Add an entry to [`boards/registry.json`](../boards/registry.json):

```json
{
  "id": "my-new-board",
  "name": "My New Board",
  "mcu": "ESP32-C3",
  "guide": "boards/my-new-board/README.md",
  "features": {
    "display": "ST7789",
    "resolution": "240x135",
    "touch": false
  },
  "firmware": {
    "enabled": false,
    "esptool_chip": "esp32c3",
    "fqbn": "esp32:esp32:esp32c3:...",
    "defines_enable": ["DISPLAY_ST7789"],
    "defines_disable": ["DISPLAY_ST7735", "DISPLAY_GC9A01"],
    "tft_setup": "boards/my-new-board/tft_setup.h",
    "tft_setup_id": 399,
    "esp32c3_spi_patch": true
  }
}
```

- Set `"enabled": false` until the port compiles locally.
- Set `"enabled": true` when ready for GitHub release builds.
- CI reads the registry automatically — no workflow edit needed.

---

## 5. Libraries and patches

| Task | Location |
|------|----------|
| TFT_eSPI pins | `boards/<id>/tft_setup.h` → copy to Arduino `User_Setup.h` |
| Shared TFT_eSPI copy | `patches/TFT_eSPI/Setup_*.h` (optional duplicate for docs) |
| ESP32-C3 SPI crash fix | [patches/TFT_eSPI/README.md](../patches/TFT_eSPI/README.md) |
| Other library fixes | `patches/<library>/` |

---

## 6. Document and list

1. Finish `boards/<id>/README.md` (upload steps, pin table, troubleshooting).
2. Add a row to the **Boards in this repo** table in [README.md](../README.md).
3. If it is a TFT board, extend [docs/DISPLAYS.md](DISPLAYS.md).
4. Optional: `boards/<id>/lopaka/` UI import for [lopaka.app](https://lopaka.app).

---

## 7. Test locally

```bash
copy ESP_Code\Settings.h.example ESP_Code\Settings.h   # Windows
# edit Settings.h — enable your DISPLAY_* define

# Arduino IDE: open ESP_Code/ESP_Code.ino, upload
```

Release-style binary (captive portal, same as GitHub):

```bash
bash scripts/build-firmware.sh my-new-board
# output: firmware/dist/my-new-board/
```

---

## 8. Publish firmware (optional)

When `"firmware.enabled": true` in registry:

```bash
git tag firmware-v1.1.0
git push origin firmware-v1.1.0
```

GitHub Actions builds all enabled boards and attaches `*-merged-flash.bin` to [Releases](https://github.com/ZL1LAC/duino-coin-boards/releases).

---

## Checklist (copy when starting a port)

```
[ ] Hardware pin map documented
[ ] boards/<id>/ created (new-board.sh)
[ ] DisplayHal.h / drivers (if needed)
[ ] Settings.h.example updated
[ ] tft_setup.h tested with TFT_eSPI
[ ] boards/registry.json entry
[ ] README.md + root README table
[ ] Local upload works
[ ] registry firmware.enabled = true
[ ] Tag firmware-v* for release bin
```

---

## Not every board looks the same

| Type | Typical work |
|------|----------------|
| ESP32-C3 + TFT | Same as Mini TV / round — DisplayHal + TFT_eSPI |
| ESP32-S3 + TFT | New FQBN in registry, may need different SPI patch |
| Headless ESP | Settings + partition only |
| OLED (SSD1306) | `DISPLAY_SSD1306` + board init (e.g. Heltec Vext) — no TFT_eSPI |
| Non-ESP | May fork different upstream sketch — still document under `boards/` |

When you know what the next device is, run `new-board.sh` and we can fill in the registry and `DisplayHal` block together.
