# Generic board test

Minimal **display + serial** sketch for hardware bring-up. No mining, no WiFi, no `ESP_Code/` sync.

Use this first on a new board; graduate to the full miner once the screen looks right.

## Quick start

1. In `testbench/<board-id>/`, copy `TestConfig.h.example` → `TestConfig.h` (edit if needed).
2. Sync config into this folder:
   ```powershell
   .\scripts\sync-testbench-test.ps1 lilygo-t-deck
   ```
3. Install TFT_eSPI User_Setup (TFT boards only — skip for Heltec OLED):
   ```powershell
   .\scripts\setup-tft-espi.ps1 lilygo-t-deck
   ```
4. Open **`testbench/GenericTest/GenericTest.ino`** in Arduino IDE.
5. Board tools from `boards/<board-id>/README.md` · Serial Monitor **115200**

You should see color bars, the board name, resolution, and `tick N` every 2s on serial.

## Files

| File | Purpose |
|------|---------|
| `GenericTest.ino` | Main sketch |
| `BoardInit.h` | Per-board power / SPI hooks (`LILYGO_T_DECK`, etc.) |
| `TestConfig.h` | Synced from `testbench/<board>/` (gitignored) |
| `TestConfig.h.example` | Template reference |

## After bring-up

When display + serial look good, switch to the real miner:

1. `testbench/<board>/Settings.h.example` → `Settings.h` (WiFi + credentials)
2. `.\scripts\sync-testbench-settings.ps1 <board-id>`
3. Upload **`ESP_Code/ESP_Code.ino`**
