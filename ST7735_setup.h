// ===========================================================================
//  TFT_eSPI setup for the Spotpear ESP32-C3 1.44" "Mini TV" board (ST7735)
// ===========================================================================
//
//  TFT_eSPI reads its display + pin configuration from a "User Setup" header.
//  The values below match this board's hardware (taken from the board's
//  schematic and the HomeDing board definition):
//
//      Display : ST7735, 128 x 128, colour order BGR
//      SCLK    : GPIO3
//      MOSI/SDA: GPIO4
//      CS      : GPIO2
//      DC / RS : GPIO0
//      RST     : GPIO5
//      Backlight (GPIO11) is hard-wired on; TFT_eSPI does not drive it.
//
//  HOW TO USE THIS FILE (pick ONE of the two methods - see README for details):
//
//  Method A (recommended - no editing of library files):
//    In Arduino IDE, this whole block can be pasted into TFT_eSPI's
//    "User_Setup.h", OR added as a new entry in "User_Setup_Select.h".
//    The README walks you through it step by step.
//
//  Method B (PlatformIO): add these as -D build_flags instead (README has the
//    ready-to-paste list).
//
//  If your screen shows a coloured border / shifted image or swapped R-B
//  colours, tweak ST7735_* driver tab and the COLOUR_ORDER - notes at bottom.
// ===========================================================================

#define USER_SETUP_INFO "Spotpear_ESP32C3_144_ST7735"

// ---- Driver ----
#define ST7735_DRIVER

// ---- Panel geometry ----
#define TFT_WIDTH  128
#define TFT_HEIGHT 128

// Black-tab 128x128 (Spotpear ESP32-C3 1.44"). Do NOT use ST7735_GREENTAB128 —
// that profile applies rowstart=32 and pushes the picture into the bottom-left.
#define ST7735_BLACKTAB

// ---- Colour order (this panel is BGR) ----
#define TFT_RGB_ORDER TFT_BGR

// ---- ESP32-C3 SPI pins for this board ----
#define TFT_MOSI 4
#define TFT_SCLK 3
#define TFT_CS    2
#define TFT_DC    0
#define TFT_RST   5
// No backlight control pin (GPIO11 is hard-wired on)
#define TFT_BL   -1

// MISO is unused for a write-only display
#define TFT_MISO -1

// ---- Fonts (keep the common ones; trims flash if you remove some) ----
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
// Skip large/smooth fonts — saves ~200 KB flash

#define SPI_FREQUENCY  20000000

// ===========================================================================
//  TROUBLESHOOTING (only if the picture looks wrong)
//  - Coloured border around the image, or image shifted by a few pixels:
//        Replace ST7735_GREENTAB128 with ONE of:
//        ST7735_INITB, ST7735_GREENTAB, ST7735_GREENTAB2,
//        ST7735_GREENTAB3, ST7735_GREENTAB160x80, ST7735_REDTAB,
//        ST7735_BLACKTAB
//  - Red and blue swapped: change TFT_BGR to TFT_RGB above.
//  - Mirrored / upside down: the firmware lets you press the BOOT button to
//        cycle rotation, so you usually don't need to change anything here.
// ===========================================================================
