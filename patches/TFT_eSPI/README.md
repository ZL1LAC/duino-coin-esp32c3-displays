# TFT_eSPI patches for ESP32-C3 display boards (Arduino ESP32 3.x)

Applies to **both** supported boards. Pick **one** setup file in `User_Setup_Select.h`.

## 1. Board setup file

Copy the file for your board into `Arduino/libraries/TFT_eSPI/User_Setups/`:

| Board | Copy this file |
|-------|----------------|
| Spotpear Mini TV (ST7735) | `Setup_Spotpear_ESP32C3_144.h` |
| ESP32-2424S012 round (GC9A01) | `Setup_ESP32_2424S012.h` |

Edit `User_Setup_Select.h` (comment out other setups):

```cpp
// Spotpear:
#include <User_Setups/Setup_Spotpear_ESP32C3_144.h>

// Round ESP32-2424S012:
// #include <User_Setups/Setup_ESP32_2424S012.h>
```

Reference copies also live in the repo: `boards/esp32c3-minitv/ST7735_setup.h`, `boards/esp32c3-round128/GC9A01_setup.h`.

## 2. ESP32-C3 SPI crash fix (required on core 3.x)

Without this patch, `tft.init()` crashes with `Store access fault` / `MTVAL: 0x10`.

In `Arduino/libraries/TFT_eSPI/Processors/TFT_eSPI_ESP32_C3.h`, after the includes, add:

```cpp
#if CONFIG_IDF_TARGET_ESP32C3
  #ifdef REG_SPI_BASE
    #undef REG_SPI_BASE
  #endif
  #define REG_SPI_BASE(i) DR_REG_SPI2_BASE
#endif
```

Also ensure `#include "soc/soc.h"` is present if `DR_REG_SPI2_BASE` is undefined.

## 3. Firmware init

| Board | Init in `DisplayHal.h` |
|-------|-------------------------|
| ST7735 Spotpear | `tft.init(INITR_GREENTAB)` |
| GC9A01 round | `tft.init()` + backlight on GPIO3 |
