/*
 * Generic board bring-up test — display + serial only (no mining, no WiFi).
 *
 * 1. testbench/<board>/TestConfig.h.example -> TestConfig.h
 * 2. .\scripts\sync-testbench-test.ps1 <board-id>
 * 3. Copy testbench/<board>/tft_setup.h -> Arduino/libraries/TFT_eSPI/User_Setup.h
 * 4. Open testbench/GenericTest/GenericTest.ino, upload
 */

#include "TestConfig.h"
#include "BoardInit.h"

#if defined(DISPLAY_ST7789) || defined(DISPLAY_ST7735) || defined(DISPLAY_GC9A01)
  #include <TFT_eSPI.h>
  TFT_eSPI tft = TFT_eSPI();
  #define HAS_TFT_DISPLAY 1
#endif

#if defined(DISPLAY_SSD1306)
  #include <U8g2lib.h>
  #include <Wire.h>
  #if defined(HELTEC_WIFI_LORA_32_V2)
    U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);
  #else
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
  #endif
  #define HAS_OLED_DISPLAY 1
#endif

#ifndef TFT_ROTATION
  #define TFT_ROTATION 1
#endif

static void drawTestScreen() {
#if defined(HAS_TFT_DISPLAY)
  int w = tft.width();
  int h = tft.height();
  int barH = h / 6;

  uint16_t colors[] = {TFT_RED, TFT_GREEN, TFT_BLUE, TFT_YELLOW, TFT_CYAN, TFT_MAGENTA};
  for (int i = 0; i < 6; i++) {
    tft.fillRect(0, i * barH, w, barH, colors[i]);
  }

  tft.fillRect(8, h / 3, w - 16, h / 3, TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(12, h / 3 + 8);
  tft.print(BOARD_NAME);
  tft.setTextSize(1);
  tft.setCursor(12, h / 3 + 32);
  tft.printf("%dx%d  rot=%d", w, h, TFT_ROTATION);
  tft.setCursor(12, h / 3 + 48);
  tft.print("Generic test OK");
  tft.drawRect(0, 0, w, h, TFT_WHITE);
#endif

#if defined(HAS_OLED_DISPLAY)
  u8g2.clearBuffer();
  for (int y = 0; y < 64; y += 8) {
    u8g2.drawBox(0, y, 128, (y / 8) % 2 ? 4 : 8);
  }
  u8g2.setDrawColor(0);
  u8g2.drawBox(4, 18, 120, 28);
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_helvB10_tr);
  u8g2.drawStr(8, 30, BOARD_NAME);
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(8, 42, "128x64  Generic test OK");
  u8g2.drawFrame(0, 0, 128, 64);
  u8g2.sendBuffer();
#endif
}

void setup() {
#if defined(HELTEC_WIFI_LORA_32_V2)
  heltec_board_early_init();
#endif
  Serial.begin(SERIAL_BAUDRATE);
  delay(800);
  Serial.println();
  Serial.println("=== duino-coin-boards generic test ===");
  Serial.println("Board: " BOARD_NAME);

#if defined(HAS_TFT_DISPLAY)
  display_init(tft, TFT_ROTATION);
  drawTestScreen();
#elif defined(HAS_OLED_DISPLAY)
  oled_init(u8g2);
  drawTestScreen();
#else
  Serial.println("No DISPLAY_* in TestConfig.h — serial-only mode");
#endif

  Serial.println("Ready. Report serial + screen in chat.");
}

void loop() {
  static uint32_t tick = 0;
  delay(2000);
  Serial.printf("[%s] tick %lu\n", BOARD_NAME, ++tick);
}
