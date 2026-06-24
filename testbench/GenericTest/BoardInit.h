#ifndef BOARD_INIT_H
#define BOARD_INIT_H

#include <Arduino.h>
#include <SPI.h>
#include "TestConfig.h"

#if defined(DISPLAY_ST7789) || defined(DISPLAY_ST7735) || defined(DISPLAY_GC9A01)
  #include <TFT_eSPI.h>
#endif

#if defined(LILYGO_T_DECK)
  #include "../../ESP_Code/TDeckDisplay.h"
#endif

#if defined(LILYGO_T_DECK_PRO)
  #include "../../ESP_Code/TDeckProDisplay.h"
#endif

#if defined(HELTEC_WIFI_LORA_32_V2)
  #include "../../ESP_Code/HeltecDisplay.h"
#endif

#if defined(LILYGO_T_BEAM_V11)
  #include "../../ESP_Code/TBeamDisplay.h"
#endif

#if defined(DISPLAY_GDEQ031T10)
  #include <GxEPD2_BW.h>
#endif

#if defined(DISPLAY_SSD1306)
  #include <U8g2lib.h>
#endif

#if defined(DISPLAY_ST7735)
  #ifndef MINITV_SPI_SCLK
    #define MINITV_SPI_SCLK 3
  #endif
  #ifndef MINITV_SPI_MOSI
    #define MINITV_SPI_MOSI 4
  #endif
#endif

#if defined(DISPLAY_GC9A01)
  #ifndef ROUND_SPI_SCLK
    #define ROUND_SPI_SCLK 6
  #endif
  #ifndef ROUND_SPI_MOSI
    #define ROUND_SPI_MOSI 7
  #endif
  #ifndef ROUND_TFT_BL
    #define ROUND_TFT_BL 3
  #endif
#endif

#if defined(TOUCH_CST816D)
  #include "../../ESP_Code/CST816D.h"
  #ifndef ROUND_TOUCH_SDA
    #define ROUND_TOUCH_SDA 4
  #endif
  #ifndef ROUND_TOUCH_SCL
    #define ROUND_TOUCH_SCL 5
  #endif
  #ifndef ROUND_TOUCH_RST
    #define ROUND_TOUCH_RST 1
  #endif
  #ifndef ROUND_TOUCH_INT
    #define ROUND_TOUCH_INT 0
  #endif
#endif

inline void board_power_init() {
#if defined(LILYGO_T_DECK)
  Serial.println("T-Deck: power + CS (via tdeck_display_init)");
#endif
}

inline void board_spi_init() {
#if defined(LILYGO_T_DECK)
  // handled in tdeck_display_init
#elif defined(DISPLAY_ST7735)
  SPI.begin(MINITV_SPI_SCLK, -1, MINITV_SPI_MOSI, -1);
  Serial.println("Mini TV: SPI 3/4");
#elif defined(DISPLAY_GC9A01)
  SPI.begin(ROUND_SPI_SCLK, -1, ROUND_SPI_MOSI, -1);
  pinMode(ROUND_TFT_BL, OUTPUT);
  analogWrite(ROUND_TFT_BL, 255);
  Serial.println("Round GC9A01: SPI 6/7");
#endif
}

#if defined(TOUCH_CST816D)
inline bool touch_i2c_probe() {
  Wire.beginTransmission(I2C_ADDR_CST816D);
  return Wire.endTransmission() == 0;
}

inline void touch_init(CST816D &touch) {
  touch.begin();
  pinMode(ROUND_TOUCH_INT, INPUT);
  Serial.print("Touch: I2C 0x15 ");
  Serial.println(touch_i2c_probe() ? "OK" : "MISSING");
  Serial.println("Touch test: tap / long-press / swipe up-down");
}

inline bool touch_poll(CST816D &touch, uint16_t *x, uint16_t *y, uint8_t *gesture) {
  return touch.getTouch(x, y, gesture);
}
#endif

#if defined(DISPLAY_ST7789) || defined(DISPLAY_ST7735) || defined(DISPLAY_GC9A01)
template<typename Tft>
inline void display_init(Tft &tft, uint8_t rotation) {
  board_power_init();
  board_spi_init();

#if defined(LILYGO_T_DECK)
  Serial.println("T-Deck: tft.begin()...");
  tdeck_display_init(tft, rotation);
#elif defined(DISPLAY_ST7735) || defined(DISPLAY_GC9A01)
  tft.init();
#else
  tft.begin();
#endif

#if !defined(LILYGO_T_DECK)
  tft.setRotation(rotation);
  tft.fillScreen(TFT_BLACK);
#endif

  Serial.printf("Display init OK — %dx%d @ rot %u\n", tft.width(), tft.height(), rotation);
}
#endif  // DISPLAY_ST7789 || DISPLAY_ST7735 || DISPLAY_GC9A01

#if defined(DISPLAY_GDEQ031T10)
template<typename EpdType>
inline void epd_init(EpdType &epd, uint8_t rotation) {
#if defined(LILYGO_T_DECK_PRO)
  Serial.println("T-Deck Pro: e-paper init...");
  tdeck_pro_display_init(epd, rotation);
#else
  epd.init(115200, true, 2, false);
  epd.setRotation(rotation);
  epd.setFullWindow();
  epd.fillScreen(GxEPD_WHITE);
  epd.display(false);
#endif
  Serial.printf("Display init OK — %dx%d @ rot %u\n", epd.width(), epd.height(), rotation);
}
#endif

#if defined(DISPLAY_SSD1306)
template<typename U8G2Type>
inline void oled_init(U8G2Type &u8g2) {
#if defined(HELTEC_WIFI_LORA_32_V2)
  Serial.println("Heltec: OLED init (SW I2C 15/4)...");
  heltec_display_init(u8g2);
#elif defined(LILYGO_T_BEAM_V11)
  Serial.println("T-Beam: AXP192 + OLED init (HW I2C 21/22)...");
  tbeam_display_init(u8g2);
#else
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  u8g2.sendBuffer();
#endif
  Serial.println("Display init OK — 128x64 OLED");
}
#endif

#endif
