/*
 * Generic board bring-up test — display + serial only (no mining, no WiFi).
 *
 * 1. testbench/<board>/TestConfig.h.example -> TestConfig.h
 * 2. .\scripts\sync-device.ps1 <device-id> test
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
  #elif defined(LILYGO_T_BEAM_V11)
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
  #else
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
  #endif
  #define HAS_OLED_DISPLAY 1
#endif

#if defined(DISPLAY_GDEQ031T10)
  #include "../../ESP_Code/TDeckProDisplay.h"
  #include <GxEPD2_BW.h>
  #ifndef TDECK_PRO_EPD_RST
    #define TDECK_PRO_EPD_RST 16
  #endif
  GxEPD2_BW<GxEPD2_310_GDEQ031T10, GxEPD2_310_GDEQ031T10::HEIGHT> epd(
    GxEPD2_310_GDEQ031T10(TDECK_PRO_EPD_CS, TDECK_PRO_EPD_DC, TDECK_PRO_EPD_RST, TDECK_PRO_EPD_BUSY));
  #define HAS_EPD_DISPLAY 1
#endif

#ifndef TFT_ROTATION
  #define TFT_ROTATION 1
#endif

#if defined(TOUCH_CST816D)
  #include <Preferences.h>
  CST816D touch(ROUND_TOUCH_SDA, ROUND_TOUCH_SCL, ROUND_TOUCH_RST, ROUND_TOUCH_INT);
  static Preferences test_prefs;
  static uint8_t test_bl = 255;
  static bool test_bl_dim = false;
  static uint8_t test_rotation = TFT_ROTATION;
  static uint8_t test_page = 0;
  static bool test_blank = false;
  static unsigned long last_touch_ms = 0;
#else
  static uint8_t test_rotation = TFT_ROTATION;
#endif

static void drawTestScreen() {
#if defined(HAS_TFT_DISPLAY)
  #if defined(TOUCH_CST816D)
  if (test_blank) {
    tft.fillScreen(TFT_BLACK);
    return;
  }
  #endif

  int w = tft.width();
  int h = tft.height();

  #if defined(TOUCH_CST816D)
  if (test_page == 1) {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GOLD, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(12, 40);
    tft.print("Stats page");
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(12, 70);
    tft.printf("rot=%d  bl=%u", test_rotation, test_bl);
    tft.setCursor(12, 88);
    tft.print("swipe right = mining");
    tft.fillCircle(114, h - 20, 2, TFT_DARKGREY);
    tft.fillCircle(126, h - 20, 2, TFT_CYAN);
    tft.drawRect(0, 0, w, h, TFT_WHITE);
    return;
  }
  #endif

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
  tft.printf("%dx%d  rot=%d", w, h, test_rotation);
  tft.setCursor(12, h / 3 + 48);
  #if defined(TOUCH_CST816D)
    tft.print("dbl=blank swipe L/R");
    tft.fillCircle(114, h - 20, 2, TFT_CYAN);
    tft.fillCircle(126, h - 20, 2, TFT_DARKGREY);
  #else
    tft.print("Generic test OK");
  #endif
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

#if defined(HAS_EPD_DISPLAY)
  epd.setFullWindow();
  epd.fillScreen(GxEPD_WHITE);
  int w = epd.width();
  int h = epd.height();
  int bandH = h / 6;
  for (int i = 0; i < 6; i++) {
    if (i % 2) {
      epd.fillRect(0, i * bandH, w, bandH, GxEPD_BLACK);
    }
  }
  epd.fillRect(8, h / 3, w - 16, h / 3, GxEPD_WHITE);
  epd.setTextColor(GxEPD_BLACK);
  epd.setTextSize(2);
  epd.setCursor(12, h / 3 + 20);
  epd.print(BOARD_NAME);
  epd.setTextSize(1);
  epd.setCursor(12, h / 3 + 44);
  epd.printf("%dx%d  rot=%d", w, h, TFT_ROTATION);
  epd.setCursor(12, h / 3 + 58);
  epd.print("Generic test OK");
  epd.drawRect(0, 0, w, h, GxEPD_BLACK);
  epd.display(false);
#endif
}

#if defined(TOUCH_CST816D) && defined(HAS_TFT_DISPLAY)
static void handleTouchGesture(uint8_t gesture) {
  if (millis() - last_touch_ms < 250) return;
  last_touch_ms = millis();

  if (test_blank) {
    if (gesture == SingleTap) {
      test_blank = false;
      analogWrite(ROUND_TFT_BL, test_bl);
      drawTestScreen();
      Serial.println("Touch: wake");
    }
    return;
  }

  if (gesture == DoubleTap) {
    test_blank = true;
    analogWrite(ROUND_TFT_BL, 0);
    tft.fillScreen(TFT_BLACK);
    Serial.println("Touch: blank");
  } else if (gesture == SlideUp || gesture == SlideDown) {
    if (gesture == SlideUp) {
      test_bl = min(255, (int)test_bl + 35);
    } else {
      test_bl = max(20, (int)test_bl - 35);
    }
    test_bl_dim = (test_bl <= 40);
    analogWrite(ROUND_TFT_BL, test_bl);
    test_prefs.begin("gc9a01_ui", false);
    test_prefs.putUChar("brightness", test_bl);
    test_prefs.end();
    Serial.printf("Touch: brightness %u\n", test_bl);
  } else if (gesture == LongPress) {
    test_bl_dim = !test_bl_dim;
    test_bl = test_bl_dim ? 40 : 255;
    analogWrite(ROUND_TFT_BL, test_bl);
    test_prefs.begin("gc9a01_ui", false);
    test_prefs.putUChar("brightness", test_bl);
    test_prefs.end();
    Serial.printf("Touch: %s\n", test_bl_dim ? "dim" : "bright");
  } else if (gesture == SlideLeft) {
    test_page = 1;
    drawTestScreen();
    Serial.println("Touch: stats page");
  } else if (gesture == SlideRight) {
    test_page = 0;
    drawTestScreen();
    Serial.println("Touch: main page");
  } else if (gesture == SingleTap) {
    test_rotation = (test_rotation + 1) % 4;
    tft.setRotation(test_rotation);
    test_prefs.begin("gc9a01_ui", false);
    test_prefs.putUChar("rotation", test_rotation);
    test_prefs.end();
    drawTestScreen();
    Serial.printf("Touch: rotation %u\n", test_rotation);
  }
}
#endif

void setup() {
#if defined(HELTEC_WIFI_LORA_32_V2)
  heltec_board_early_init();
#endif
#if defined(LILYGO_T_BEAM_V11)
  tbeam_board_early_init();
#endif
  Serial.begin(SERIAL_BAUDRATE);
  delay(800);
  Serial.println();
  Serial.println("=== duino-coin-boards generic test ===");
  Serial.println("Board: " BOARD_NAME);

#if defined(HAS_TFT_DISPLAY)
  display_init(tft, TFT_ROTATION);
  #if defined(TOUCH_CST816D)
    test_prefs.begin("gc9a01_ui", true);
    test_rotation = test_prefs.getUChar("rotation", TFT_ROTATION) % 4;
    test_bl = test_prefs.getUChar("brightness", 255);
    test_prefs.end();
    tft.setRotation(test_rotation);
    analogWrite(ROUND_TFT_BL, test_bl);
    touch_init(touch);
  #endif
  drawTestScreen();
#elif defined(HAS_OLED_DISPLAY)
  oled_init(u8g2);
  drawTestScreen();
#elif defined(HAS_EPD_DISPLAY)
  epd_init(epd, TFT_ROTATION);
  drawTestScreen();
#else
  Serial.println("No DISPLAY_* in TestConfig.h — serial-only mode");
#endif

  Serial.println("Ready. Report serial + screen in chat.");
}

void loop() {
#if defined(TOUCH_CST816D) && defined(HAS_TFT_DISPLAY)
  static uint8_t gesture_done = None;
  uint16_t x = 0, y = 0;
  uint8_t gesture = None;
  bool down = touch_poll(touch, &x, &y, &gesture);
  if (gesture == None) {
    gesture_done = None;
  } else if (gesture != gesture_done) {
    gesture_done = gesture;
    handleTouchGesture(gesture);
  }
  if (down && !test_blank) {
    tft.drawCircle(x, y, 6, TFT_WHITE);
    tft.drawCircle(x, y, 7, TFT_BLACK);
  }
  delay(20);
#else
  static uint32_t tick = 0;
  delay(2000);
  Serial.printf("[%s] tick %lu\n", BOARD_NAME, ++tick);
#endif
}
