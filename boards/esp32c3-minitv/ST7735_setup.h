// TFT_eSPI setup for the Spotpear ESP32-C3 1.44" "Mini TV" board (ST7735)
// See boards/esp32c3-minitv/README.md and docs/DISPLAYS.md

#define USER_SETUP_INFO "Spotpear_ESP32C3_144_ST7735"

#define ST7735_DRIVER

#define TFT_WIDTH  128
#define TFT_HEIGHT 128

#define ST7735_BLACKTAB

#define TFT_RGB_ORDER TFT_BGR

#define TFT_MOSI 4
#define TFT_SCLK 3
#define TFT_CS    2
#define TFT_DC    0
#define TFT_RST   5
#define TFT_BL   -1
#define TFT_MISO -1

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4

#define SPI_FREQUENCY 20000000
