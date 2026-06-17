// TFT_eSPI user setup for ESP32-C3 1.28" round display (ESP32-2424S012)
// GC9A01 driver, 240x240 IPS round panel (~37 mm)
// Mining UI matches Spotpear Mini TV — see docs/DISPLAYS.md for board comparison
//
// Install steps:
// 1. Copy this file to Arduino/libraries/TFT_eSPI/User_Setups/Setup_ESP32_2424S012.h
// 2. In User_Setup_Select.h, comment out other setups and add:
//    #include <User_Setups/Setup_ESP32_2424S012.h>
// 3. Apply the ESP32-C3 SPI patch in patches/TFT_eSPI/README.md (core 3.x)
//
// Pinout (on-board, fixed):
//   Display SPI — SCLK=6, MOSI=7, CS=10, DC=2, RST=-1, BL=3
//   Touch I2C (CST816D, 2424S012C only) — SDA=4, SCL=5, INT=0, RST=1, addr=0x15

#define USER_SETUP_ID 301
#define USER_SETUP_INFO "ESP32_2424S012_GC9A01"

#define GC9A01_DRIVER

#define TFT_WIDTH  240
#define TFT_HEIGHT 240

#define TFT_MOSI 7
#define TFT_SCLK 6
#define TFT_CS   10
#define TFT_DC   2
#define TFT_RST  -1
#define TFT_BL   3
#define TFT_MISO -1

#define TFT_BACKLIGHT_ON HIGH

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF
#define SMOOTH_FONT

#define SPI_FREQUENCY       40000000
#define SPI_READ_FREQUENCY  20000000
