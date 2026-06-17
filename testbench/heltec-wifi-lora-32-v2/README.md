# Heltec WiFi LoRa 32 V2 — testbench

**Board guide:** [boards/heltec-wifi-lora-32-v2/](../../boards/heltec-wifi-lora-32-v2/)

## Generic test

1. `TestConfig.h.example` → `TestConfig.h`
2. `.\scripts\sync-testbench-test.ps1 heltec-wifi-lora-32-v2`
3. Install **U8g2** library (no TFT_eSPI)
4. Upload `testbench/GenericTest/GenericTest.ino` · Serial **115200**

## Full miner

1. `Settings.h.example` → `Settings.h` (WiFi + credentials)
2. `.\scripts\sync-testbench-settings.ps1 heltec-wifi-lora-32-v2`
3. Upload `ESP_Code/ESP_Code.ino`
