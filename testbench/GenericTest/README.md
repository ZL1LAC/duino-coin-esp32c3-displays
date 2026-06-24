# Generic board test

Minimal **display + serial** sketch for hardware bring-up. No mining, no WiFi.

Device config lives in **`devices/<id>/`** — sync it here before upload.

## Quick start

1. Copy `devices/<id>/TestConfig.h.example` → `devices/<id>/TestConfig.h`
2. Sync:
   ```powershell
   .\scripts\sync-device.ps1 lilygo-t-deck test
   ```
3. TFT_eSPI boards only:
   ```powershell
   .\scripts\setup-tft-espi.ps1 lilygo-t-deck
   ```
4. Open **`GenericTest.ino`** · upload · Serial **115200**

Touch boards (e.g. `esp32c3-round128`) compile `CST816D_link.cpp`, which includes the shared driver from `ESP_Code/`.

See `devices/<id>/README.md` for Arduino board settings.

## After bring-up

1. `devices/<id>/Settings.h.example` → `Settings.h` (WiFi + credentials)
2. `.\scripts\sync-device.ps1 <id> miner`
3. Upload **`ESP_Code/ESP_Code.ino`**
