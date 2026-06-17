# Duino-Coin board ports

Personal fork of [Duino-Coin](https://github.com/revoxhere/duino-coin) **ESP_Code** — adapted so mining runs on **specific boards and hardware** I use (displays, touch, pins, etc.).

Not limited to one MCU or screen type. Each board gets its own folder under `boards/` with a README and setup files.

Fork base: upstream **ESP_Code 4.3** · network: [duinocoin.com](https://duinocoin.com)

> Old repo names (`duino-coin-esp32c3-minitv`, `duino-coin-esp32c3-displays`) redirect here.

---

## Boards in this repo

| Board | MCU | Notes | Guide |
|-------|-----|-------|--------|
| Spotpear ESP32-C3 1.44" Mini TV | ESP32-C3 | ST7735 128×128 | [boards/esp32c3-minitv/](boards/esp32c3-minitv/) |
| ESP32-2424S012 round | ESP32-C3 | GC9A01 240×240, CST816D touch (C model) | [boards/esp32c3-round128/](boards/esp32c3-round128/) |

Display comparison and switching: **[docs/DISPLAYS.md](docs/DISPLAYS.md)**

More boards will be added under `boards/` — not every port will be ESP32-C3 or have a display.

---

## Quick start (current ESP32-C3 display builds)

1. **Clone**
   ```bash
   git clone https://github.com/ZL1LAC/duino-coin-boards.git
   cd duino-coin-boards
   ```

2. **Credentials** — in `ESP_Code/`:
   ```bash
   copy Settings.h.example Settings.h    # Windows
   cp Settings.h.example Settings.h      # macOS / Linux
   ```
   Set username, WiFi (2.4 GHz), and mining key.

3. **Pick hardware** in `ESP_Code/Settings.h` — enable one `DISPLAY_*` line (see your board README).

4. **Libraries / patches** — follow the README for your board (`boards/*/`, `patches/`).

5. **Upload** — open **`ESP_Code/ESP_Code.ino`** in Arduino IDE with the board settings from that README.

**Or flash a pre-built binary** — see [firmware/README.md](firmware/README.md) and [docs/FLASH.md](docs/FLASH.md) (GitHub Releases, no compile required).

---

## Repository layout

```
duino-coin-boards/
├── ESP_Code/           Arduino sketch (open ESP_Code.ino here)
├── boards/             Per-board README, TFT setup, Lopaka layouts
│   ├── esp32c3-minitv/
│   └── esp32c3-round128/
├── docs/               Shared docs (display comparison, etc.)
└── patches/            Library / toolchain fixes
```

| Path | Purpose |
|------|---------|
| `ESP_Code/` | Main miner sketch, `Settings.h.example`, `DisplayHal.h`, drivers |
| `boards/<name>/` | Board README, `*_setup.h`, optional `lopaka/` UI imports |
| `docs/` | Cross-board documentation |
| `firmware/` | Pre-built flash images (via GitHub Releases) |
| `patches/` | TFT_eSPI user setups and ESP32-C3 fixes |

---

## Adding a new board

1. Create `boards/<short-name>/README.md`.
2. Add board-specific setup files and patches (only what that board needs).
3. Extend `ESP_Code/` if the port needs new firmware code.
4. List the board in this README.

---

## Upstream

[revoxhere/duino-coin](https://github.com/revoxhere/duino-coin)

## License

MIT — see [LICENSE](LICENSE).
