# Duino-Coin — Spotpear ESP32-C3 Mini TV (ST7735)

Fork of [Duino-Coin](https://github.com/revoxhere/duino-coin) with display support for the **Spotpear ESP32-C3 1.44" "Mini TV"** board — a 128×128 **ST7735** screen with live mining stats.

Based on Duino-Coin **ESP_Code 4.3**.

---

## What's new in this repo

### Firmware (repo root)

| File | Change |
|------|--------|
| `DisplayHal.h` | Full 128×128 ST7735 mining UI (hashrate, shares, diff, ping, node, IP, uptime). Layout tuned in [Lopaka](https://lopaka.app). `INITR_GREENTAB` init for correct panel alignment on this board. |
| `ESP_Code.ino` | Display hooks for ST7735; miner init before display; USB-CDC friendly serial; WiFi timeout tweaks for ESP32-C3. |
| `Settings.h.example` | Template with `#define DISPLAY_ST7735` and 115200 serial baud. Copy to `Settings.h` and add your credentials. |
| `ST7735_setup.h` | TFT_eSPI pin/driver reference for this board. |
| `README_ESP32C3_MiniTV.md` | Step-by-step Arduino IDE, library, and upload guide. |

### TFT_eSPI patches (`patches/TFT_eSPI/`)

| File | Change |
|------|--------|
| `Setup_Spotpear_ESP32C3_144.h` | User setup for Spotpear pins (SCLK=3, MOSI=4, CS=2, DC=0, RST=5). |
| `README.md` | ESP32-C3 **SPI crash fix** for Arduino ESP32 core 3.x (`REG_SPI_BASE` / `MTVAL: 0x10`). |

### Board details

- **MCU:** ESP32-C3  
- **Display:** ST7735, 128×128, BGR  
- **BOOT button (GPIO9):** cycles screen rotation  
- **LED blinking:** disabled on this board (GPIO11 flash / GPIO8 button conflict)

---

## Quick start

1. Clone this repo.
2. Copy `Settings.h.example` → `Settings.h` and set your Duino-Coin username, WiFi, etc.
3. Follow **`README_ESP32C3_MiniTV.md`** for Arduino IDE, libraries, and TFT_eSPI setup.
4. Apply the files in **`patches/TFT_eSPI/`** to your local TFT_eSPI library (required on ESP32 core 3.x).
5. Open `ESP_Code.ino`, select **ESP32C3 Dev Module**, upload.

**Arduino settings that worked:** USB CDC On Boot **Enabled**, partition **Huge APP**, upload speed **115200**.

---

## Mining screen layout

```
┌──────────────────────────────┐
│ ▂▄▆█  10ms   darkhunter~     │
├──────────────────────────────┤
│  63.4              kH/s      │
├──────────────────────────────┤
│  6400          diff          │
│  0.2           sh/s          │
├──────────────────────────────┤
│ ✓ 110/110         (100%)     │
├──────────────────────────────┤
│ 192.168.x.x        0h9m24s   │
└──────────────────────────────┘
```

---

## Upstream

This project mines on the [Duino-Coin](https://duinocoin.com) network. For the official wallet, miners, and docs see [revoxhere/duino-coin](https://github.com/revoxhere/duino-coin).

---

## License

Same as upstream Duino-Coin — see [LICENSE](LICENSE).
