// Abstraction layer for handling various types of screens
// See Settings.h for enabling the screen of your choice
#ifndef DISPLAY_HAL_H
#define DISPLAY_HAL_H

// Abstraction layer: custom fonts, images, etc.
#if defined(DISPLAY_SSD1306)
    static const unsigned char image_check_contour_bits[] U8X8_PROGMEM = {0x00,0x04,0x00,0x0a,0x04,0x11,0x8a,0x08,0x51,0x04,0x22,0x02,0x04,0x01,0x88,0x00,0x50,0x00,0x20,0x00};
    static const unsigned char image_network_1_bar_bits[] U8X8_PROGMEM = {0x00,0x70,0x00,0x50,0x00,0x50,0x00,0x50,0x00,0x57,0x00,0x55,0x00,0x55,0x00,0x55,0x70,0x55,0x50,0x55,0x50,0x55,0x50,0x55,0x57,0x55,0x57,0x55,0x77,0x77,0x00,0x00};
    static const unsigned char image_network_2_bars_bits[] U8X8_PROGMEM = {0x00,0x70,0x00,0x50,0x00,0x50,0x00,0x50,0x00,0x57,0x00,0x55,0x00,0x55,0x00,0x55,0x70,0x55,0x70,0x55,0x70,0x55,0x70,0x55,0x77,0x55,0x77,0x55,0x77,0x77,0x00,0x00};
    static const unsigned char image_network_3_bars_bits[] U8X8_PROGMEM = {0x00,0x70,0x00,0x50,0x00,0x50,0x00,0x50,0x00,0x57,0x00,0x57,0x00,0x57,0x00,0x57,0x70,0x57,0x70,0x57,0x70,0x57,0x70,0x57,0x77,0x57,0x77,0x57,0x77,0x77,0x00,0x00};
    static const unsigned char image_network_4_bars_bits[] U8X8_PROGMEM = {0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x77,0x00,0x77,0x00,0x77,0x00,0x77,0x70,0x77,0x70,0x77,0x70,0x77,0x70,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x00,0x00};
    static const unsigned char image_duco_logo_bits[] U8X8_PROGMEM = {0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x00,0xff,0x00,0xc0,0x01,0x9f,0x01,0x20,0x01,0x20,0x01,0x20,0x01,0x9f,0x01,0xc0,0x01,0xff,0x00,0x7f,0x00};
    static const unsigned char image_duco_logo_big_bits[] U8X8_PROGMEM = {0x00,0x00,0x00,0x00,0x00,0x00,0xfc,0xff,0xff,0x01,0x00,0x00,0xfc,0xff,0xff,0x0f,0x00,0x00,0xfc,0xff,0xff,0x3f,0x00,0x00,0xfc,0xff,0xff,0x7f,0x00,0x00,0xfc,0xff,0xff,0xff,0x00,0x00,0xfc,0xff,0xff,0xff,0x01,0x00,0xfc,0xff,0xff,0xff,0x03,0x00,0xf8,0xff,0xff,0xff,0x07,0x00,0x00,0x00,0x00,0xfe,0x0f,0x00,0xfc,0xff,0x03,0xf8,0x0f,0x00,0xfc,0xff,0x0f,0xf0,0x1f,0x00,0xfc,0xff,0x1f,0xe0,0x1f,0x00,0xfc,0xff,0x3f,0xe0,0x3f,0x00,0xfc,0xff,0x7f,0xc0,0x3f,0x00,0xfc,0xff,0xff,0xc0,0x7f,0x00,0xf8,0xff,0xff,0x80,0x7f,0x00,0x00,0x00,0xfe,0x80,0x7f,0x00,0x00,0x00,0xfc,0x81,0x7f,0x00,0x00,0x00,0xfc,0x01,0x7f,0x00,0x00,0x00,0xfc,0x01,0xff,0x00,0x00,0x00,0xfc,0x01,0xff,0x00,0x00,0x00,0xfc,0x01,0xff,0x00,0x00,0x00,0xfc,0x01,0xff,0x00,0x00,0x00,0xfc,0x01,0xff,0x00,0x00,0x00,0xfc,0x81,0x7f,0x00,0x00,0x00,0xfe,0x81,0x7f,0x00,0x00,0x80,0xff,0x80,0x7f,0x00,0xfc,0xff,0xff,0xc0,0x7f,0x00,0xfc,0xff,0xff,0xc0,0x7f,0x00,0xfc,0xff,0x7f,0xe0,0x3f,0x00,0xfc,0xff,0x3f,0xf0,0x3f,0x00,0xfc,0xff,0x1f,0xf8,0x1f,0x00,0xfc,0xff,0x0f,0xfc,0x1f,0x00,0xf8,0xff,0x01,0xfe,0x0f,0x00,0x00,0x00,0xc0,0xff,0x0f,0x00,0xfc,0xff,0xff,0xff,0x07,0x00,0xfc,0xff,0xff,0xff,0x03,0x00,0xfc,0xff,0xff,0xff,0x01,0x00,0xfc,0xff,0xff,0xff,0x00,0x00,0xfc,0xff,0xff,0x7f,0x00,0x00,0xfc,0xff,0xff,0x1f,0x00,0x00,0xfc,0xff,0xff,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
#endif

#if defined(DISPLAY_16X2)
    static byte duco_logo[] = {0x1E, 0x01, 0x1D, 0x05, 0x1D, 0x01, 0x1E, 0x00};
    static byte check_mark[] = {0x00, 0x00, 0x00, 0x01, 0x02,0x14, 0x08, 0x00};
    static byte kh[] = {0x08, 0x0A, 0x0C, 0x0A, 0x00, 0x0A, 0x0E, 0x0A};
    static byte msec[] = {0x0A, 0x15, 0x11, 0x06, 0x08, 0x04, 0x02, 0x0C};
#endif

#if defined(DISPLAY_ST7789)
    // Define colors
    #define WHITE       TFT_WHITE
    #define BLACK       TFT_BLACK
    #define DUCO_GOLD   0xFD20
    #define DUCO_GRAY   0x7BEF
    #define DUCO_DARK   0x39E7
    #define DUCO_GREEN  0x07E0
    #define DUCO_CYAN   0x07FF

    // Button and rotation
    #define TFT_BUTTON_PIN 0  // Boot button on T-Display S3
    uint8_t tft_rotation = 1; // 0,1,2,3 = 4 orientations
    volatile bool tft_rotation_changed = false;

    // Interrupt handler - fires instantly on button press
    void IRAM_ATTR buttonISR() {
      tft_rotation_changed = true;
    }

    // Draw WiFi signal bars
    void drawWifiBars(int x, int y) {
      int rssi = WiFi.RSSI();
      int bars = (rssi > -40) ? 4 : (rssi > -60) ? 3 : (rssi > -75) ? 2 : 1;
      for (int i = 0; i < 4; i++) {
        int barH = 6 + i * 5;
        int barY = y + 20 - barH;
        uint16_t color = (i < bars) ? DUCO_GREEN : DUCO_DARK;
        tft.fillRect(x + i * 9, barY, 7, barH, color);
      }
    }

    // Draw checkmark icon
    void drawCheckmark(int x, int y) {
      tft.drawLine(x, y+8, x+5, y+13, DUCO_GREEN);
      tft.drawLine(x+1, y+8, x+6, y+13, DUCO_GREEN);
      tft.drawLine(x+5, y+13, x+14, y+2, DUCO_GREEN);
      tft.drawLine(x+6, y+13, x+15, y+2, DUCO_GREEN);
    }

    // State flags
    bool tft_layout_drawn = false;
    volatile bool tft_busy = false;

    // Apply rotation change (called from main loop, not ISR)
    void checkButton() {
      if (tft_rotation_changed) {
        tft_rotation_changed = false;
        tft_rotation = (tft_rotation + 1) % 4; // Cycle: 0→1→2→3→0
        tft.setRotation(tft_rotation);
        tft_layout_drawn = false;
      }
    }

    // Check if current rotation is landscape (1 or 3) or portrait (0 or 2)
    bool isLandscape() {
      return (tft_rotation == 1 || tft_rotation == 3);
    }

    // Draw static layout (separators + labels)
    void drawStaticLayout() {
      tft.fillScreen(BLACK);
      tft.setTextColor(DUCO_GRAY, BLACK);

      if (isLandscape()) {
        // === LANDSCAPE 320x170 ===
        tft.drawFastHLine(0, 28, 320, DUCO_DARK);
        tft.drawFastHLine(0, 105, 320, DUCO_DARK);
        tft.drawFastHLine(0, 140, 320, DUCO_DARK);
        tft.drawFastHLine(200, 55, 115, DUCO_DARK);
        // diff and shr/s labels on right side (static)
        tft.setTextSize(1);
        tft.setCursor(280, 40);
        tft.print("diff");
        tft.setCursor(274, 65);
        tft.print("shr/s");
        tft.setCursor(5, 147);
        tft.print("Duino-Coin " + String(SOFTWARE_VERSION));
      } else {
        // === PORTRAIT 170x320 ===
        tft.drawFastHLine(0, 28, 170, DUCO_DARK);
        tft.drawFastHLine(0, 130, 170, DUCO_DARK);
        tft.drawFastHLine(0, 195, 170, DUCO_DARK);
        tft.drawFastHLine(0, 255, 170, DUCO_DARK);
        // kH/s label centered
        tft.setTextSize(2);
        tft.setCursor(55, 100);
        tft.print("kH/s");
        // Bottom version
        tft.setTextSize(1);
        tft.setCursor(5, 262);
        tft.print("Duino-Coin " + String(SOFTWARE_VERSION));
      }
      tft_layout_drawn = true;
    }
#endif

// ===================================================================== //
//  ST7735 128x128 support (Spotpear ESP32-C3 1.44" "Mini TV" board)     //
//  Uses the TFT_eSPI library. The display pins are set via TFT_eSPI's   //
//  build configuration - see boards/esp32c3-minitv/ST7735_setup.h              //
//  and the README for how to point TFT_eSPI at it.                      //
// ===================================================================== //
#if defined(DISPLAY_ST7735)
    // Colors (RGB565)
    #define WHITE       TFT_WHITE
    #define BLACK       TFT_BLACK
    #define DUCO_GOLD   0xFD20
    #define DUCO_GRAY   0x7BEF
    #define DUCO_DARK   0x39E7
    #define DUCO_GREEN  0x07E0
    #define DUCO_CYAN   0x07FF

    // Spotpear 1.44" ST7735 — GREENTAB init sets colstart=2 (fixes right-edge garbage).
    // Do not use setViewport X shift: it leaves the left columns uncleared (static noise).
    #define ST7735_X_OFS  (0)
    #define ST7735_Y_OFS  (0)

    void st7735_apply_viewport() {
      tft.resetViewport();
    }

    // fillScreen must run on the full panel, not a shifted viewport
    void st7735_clear_screen() {
      tft.resetViewport();
      tft.fillScreen(BLACK);
    }

    // The board's only freely-usable button is BOOT on GPIO9. Pressing it cycles
    // the screen rotation, so you can mount the board in any orientation.
    #define TFT_BUTTON_PIN 9
    uint8_t tft_rotation = 0;            // 0..3 = four orientations
    volatile bool tft_rotation_changed = false;
    bool tft_layout_drawn = false;
    volatile bool tft_busy = false;      // guards against both cores drawing at once

    void IRAM_ATTR buttonISR() {
      tft_rotation_changed = true;
    }

    void checkButton() {
      if (tft_rotation_changed) {
        tft_rotation_changed = false;
        tft_rotation = (tft_rotation + 1) % 4;
        tft.setRotation(tft_rotation);
        st7735_apply_viewport();
        tft_layout_drawn = false;
      }
    }

    // Small WiFi signal-strength bars
    void drawWifiBars(int x, int y) {
      int rssi = WiFi.RSSI();
      int bars = (rssi > -40) ? 4 : (rssi > -60) ? 3 : (rssi > -75) ? 2 : 1;
      for (int i = 0; i < 4; i++) {
        int barH = 3 + i * 3;
        int barY = y + 12 - barH;
        uint16_t color = (i < bars) ? DUCO_GREEN : DUCO_DARK;
        tft.fillRect(x + i * 5, barY, 4, barH, color);
      }
    }

    // Small checkmark icon
    void drawCheckmark(int x, int y) {
      tft.drawLine(x, y+5, x+3, y+8, DUCO_GREEN);
      tft.drawLine(x+1, y+5, x+4, y+8, DUCO_GREEN);
      tft.drawLine(x+3, y+8, x+9, y+1, DUCO_GREEN);
      tft.drawLine(x+4, y+8, x+10, y+1, DUCO_GREEN);
    }

    // Truncate a string so it fits on one text line (6 px/char at size 1 on this panel)
    String st7735_fit(String s, uint8_t maxChars) {
      if ((int)s.length() <= maxChars) return s;
      if (maxChars < 2) return s.substring(0, maxChars);
      return s.substring(0, maxChars - 1) + "~";
    }

    // Compact accept-rate label, e.g. "(100%)"
    String st7735_pct(String rate) {
      return "(" + String((int)rate.toFloat()) + "%)";
    }

    // Right edge for size-1 text (GREENTAB colstart eats ~2px on the right)
    #define ST7735_TEXT_RIGHT 120

    void st7735_print_right(String s, int y) {
      int w = s.length() * 6;
      tft.setCursor(ST7735_TEXT_RIGHT - w, y);
      tft.print(s);
    }

    // Static layout — coordinates from Lopaka drawScreen_1
    void drawStaticLayout() {
      st7735_clear_screen();
      tft.fillRect(0, 25,  128, 1, DUCO_DARK);
      tft.fillRect(0, 66,  128, 1, DUCO_DARK);
      tft.fillRect(0, 96,  128, 1, DUCO_DARK);
      tft.fillRect(0, 116, 128, 1, DUCO_DARK);
      tft.setTextColor(DUCO_GRAY, BLACK);
      tft.setTextSize(1);
      tft.setCursor(70, 74);
      tft.print("diff");
      tft.setCursor(70, 86);
      tft.print("sh/s");
      tft_layout_drawn = true;
    }
#endif

// ===================================================================== //
// GC9A01 240x240 round display (ESP32-C3 1.28" ESP32-2424S012 board)    //
// Same mining UI as Spotpear Mini TV (DISPLAY_ST7735) — Lopaka layout.  //
// Scaled 128x128 -> 240x240 with side inset for the round visible area. //
// Driver/pins: boards/esp32c3-round128/GC9A01_setup.h                        //
// ===================================================================== //
#if defined(DISPLAY_GC9A01)
    #define WHITE       TFT_WHITE
    #define BLACK       TFT_BLACK
    #define DUCO_GOLD   0xFD20
    #define DUCO_GRAY   0x7BEF
    #define DUCO_DARK   0x39E7
    #define DUCO_GREEN  0x07E0
    #define DUCO_CYAN   0x07FF

    // Scale Spotpear 128x128 Lopaka coords onto 240x240 round panel
    #define GC9A01_MX 32
    #define GC9A01_W  176
    #define GC9A01_MY 28
    #define GC9A01_SY(y) (GC9A01_MY + ((y) * 184) / 128)
    #define GC9A01_SX(x) (GC9A01_MX + ((x) * GC9A01_W) / 128)
    #define GC9A01_TEXT_RIGHT (GC9A01_MX + GC9A01_W - 8)

    #ifndef TFT_BL
      #define TFT_BL 3
    #endif

    #define TFT_BUTTON_PIN 9
    uint8_t tft_rotation = 0;
    volatile bool tft_rotation_changed = false;
    bool tft_layout_drawn = false;
    volatile bool tft_busy = false;

    void IRAM_ATTR buttonISR() {
      tft_rotation_changed = true;
    }

    void checkButton() {
      if (tft_rotation_changed) {
        tft_rotation_changed = false;
        tft_rotation = (tft_rotation + 1) % 4;
        tft.setRotation(tft_rotation);
        tft_layout_drawn = false;
      }
    }

#if defined(TOUCH_CST816D)
    static bool touch_was_down = false;
    static unsigned long last_touch_action_ms = 0;
    static uint8_t gc9a01_bl_level = 255;
    static bool touch_present = false;
    volatile bool touch_irq_pending = false;

    void IRAM_ATTR touchISR() {
      touch_irq_pending = true;
    }

    bool touch_i2c_probe() {
      Wire.beginTransmission(I2C_ADDR_CST816D);
      return Wire.endTransmission() == 0;
    }

    void touch_setup_gc9a01() {
      touch.begin();
      touch_present = touch_i2c_probe();
      pinMode(0, INPUT);
      attachInterrupt(digitalPinToInterrupt(0), touchISR, FALLING);
      #if defined(SERIAL_PRINTING)
        Serial.print("Touch: I2C 0x15 ");
        Serial.println(touch_present ? "OK" : "MISSING");
        if (touch_present) {
          uint16_t x = 0, y = 0;
          uint8_t g = None;
          if (touch.getTouch(&x, &y, &g)) {
            Serial.printf("Touch: finger at boot X=%u Y=%u\n", x, y);
          } else {
            Serial.println("Touch: ready (tap screen to test)");
          }
        }
        Serial.flush();
      #endif
    }

    void checkTouch() {
      if (!touch_present) return;

      bool irq = touch_irq_pending;
      if (irq) {
        touch_irq_pending = false;
      }
      if (!irq && digitalRead(0) != LOW && !touch_was_down) {
        return;
      }

      uint16_t x = 0, y = 0;
      uint8_t gesture = None;
      bool down = touch.getTouch(&x, &y, &gesture);

      #if defined(SERIAL_PRINTING)
        static unsigned long last_dbg = 0;
        if (down && millis() - last_dbg > 300) {
          Serial.printf("Touch: X=%u Y=%u gesture=%u\n", x, y, gesture);
          last_dbg = millis();
        }
      #endif

      if (down && (gesture == SlideUp || gesture == SlideDown)) {
        if (millis() - last_touch_action_ms > 250) {
          last_touch_action_ms = millis();
          if (gesture == SlideUp) {
            gc9a01_bl_level = min(255, (int)gc9a01_bl_level + 35);
          } else {
            gc9a01_bl_level = max(20, (int)gc9a01_bl_level - 35);
          }
          analogWrite(TFT_BL, gc9a01_bl_level);
        }
        touch_was_down = down;
        return;
      }

      if (down && !touch_was_down) {
        if (millis() - last_touch_action_ms > 350) {
          last_touch_action_ms = millis();
          tft_rotation_changed = true;
        }
      }
      touch_was_down = down;
    }
#else
    void touch_setup_gc9a01() {}
    void checkTouch() {}
#endif

    void gc9a01_clear_screen() {
      tft.fillScreen(BLACK);
    }

    String gc9a01_fit(String s, uint8_t maxChars) {
      if ((int)s.length() <= maxChars) return s;
      if (maxChars < 2) return s.substring(0, maxChars);
      return s.substring(0, maxChars - 1) + "~";
    }

    String gc9a01_pct(String rate) {
      return "(" + String((int)rate.toFloat()) + "%)";
    }

    void gc9a01_print_right(String s, int y) {
      int w = s.length() * 6;
      tft.setCursor(GC9A01_TEXT_RIGHT - w, y);
      tft.print(s);
    }

    void drawWifiBars(int x, int y) {
      int rssi = WiFi.RSSI();
      int bars = (rssi > -40) ? 4 : (rssi > -60) ? 3 : (rssi > -75) ? 2 : 1;
      for (int i = 0; i < 4; i++) {
        int barH = 3 + i * 3;
        int barY = y + 12 - barH;
        uint16_t color = (i < bars) ? DUCO_GREEN : DUCO_DARK;
        tft.fillRect(x + i * 5, barY, 4, barH, color);
      }
    }

    void drawCheckmark(int x, int y) {
      tft.drawLine(x, y+5, x+3, y+8, DUCO_GREEN);
      tft.drawLine(x+1, y+5, x+4, y+8, DUCO_GREEN);
      tft.drawLine(x+3, y+8, x+9, y+1, DUCO_GREEN);
      tft.drawLine(x+4, y+8, x+10, y+1, DUCO_GREEN);
    }

    // Static layout — same rows as Spotpear ST7735 (Lopaka drawScreen_1)
    void drawStaticLayout() {
      gc9a01_clear_screen();
      tft.fillRect(GC9A01_MX, GC9A01_SY(25),  GC9A01_W, 1, DUCO_DARK);
      tft.fillRect(GC9A01_MX, GC9A01_SY(66),  GC9A01_W, 1, DUCO_DARK);
      tft.fillRect(GC9A01_MX, GC9A01_SY(96),  GC9A01_W, 1, DUCO_DARK);
      tft.fillRect(GC9A01_MX, GC9A01_SY(116), GC9A01_W, 1, DUCO_DARK);
      tft.setTextColor(DUCO_GRAY, BLACK);
      tft.setTextSize(1);
      tft.setCursor(GC9A01_SX(70), GC9A01_SY(74));
      tft.print("diff");
      tft.setCursor(GC9A01_SX(70), GC9A01_SY(86));
      tft.print("sh/s");
      tft_layout_drawn = true;
    }
#endif

  #if defined(DISPLAY_SSD1306)
    void drawStrMultiline(const char *msg, int xloc, int yloc) {
     //https://github.com/olikraus/u8g2/discussions/1479
     int dspwidth = u8g2.getDisplayWidth();    
     int strwidth = 0;          
     char glyph[2]; glyph[1] = 0;
  
     for (const char *ptr = msg, *lastblank = NULL; *ptr; ++ptr) {
        while (xloc == 0 && *msg == ' ')
           if (ptr == msg++) ++ptr;                     
  
        glyph[0] = *ptr;
        strwidth += u8g2.getStrWidth(glyph);                   
        if (*ptr == ' ')  lastblank = ptr;                 
        else ++strwidth;                       
  
        if (xloc + strwidth > dspwidth) {                       
           int starting_xloc = xloc;
           while (msg < (lastblank ? lastblank : ptr)) {                       
              glyph[0] = *msg++;
              xloc += u8g2.drawStr(xloc, yloc, glyph); 
           }
  
           strwidth -= xloc - starting_xloc;                       
           yloc += u8g2.getMaxCharHeight();                      
           xloc = 0; lastblank = NULL;
        }
     }
     while (*msg) {                        
        glyph[0] = *msg++;
        xloc += u8g2.drawStr(xloc, yloc, glyph);
     }
    }
#endif

#if defined(DISPLAY_SSD1306) || defined(DISPLAY_16X2) || defined(DISPLAY_ST7789) || defined(DISPLAY_ST7735) || defined(DISPLAY_GC9A01)
    void screen_setup() {
      // Ran during setup()
      // Abstraction layer: screen initialization

      #if defined(DISPLAY_SSD1306)
          u8g2.begin();
          u8g2.clearBuffer();
          u8g2.setFontMode(1);
          u8g2.setBitmapMode(1);
          u8g2.sendBuffer();
      #endif

      #if defined(DISPLAY_16X2)
          lcd.begin(16, 2);
          lcd.createChar(0, duco_logo);
          lcd.createChar(1, check_mark);
          lcd.createChar(2, kh);
          lcd.createChar(3, msec);
          lcd.home();
          lcd.clear();
      #endif

      #if defined(DISPLAY_ST7789)
        pinMode(TFT_BUTTON_PIN, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(TFT_BUTTON_PIN), buttonISR, FALLING);
        tft.begin();
        tft.setRotation(tft_rotation);
        tft.init();
        tft.fillScreen(BLACK);
      #endif

      #if defined(DISPLAY_ST7735)
        #if defined(SERIAL_PRINTING)
          Serial.println("LCD: SPI.begin (pins 3,4)...");
          Serial.flush();
        #endif
        // Spotpear ESP32-C3: SCLK=GPIO3 MOSI=GPIO4 — prime the bus before TFT_eSPI init
        SPI.begin(3, -1, 4, -1);
        #if defined(SERIAL_PRINTING)
          Serial.println("LCD: tft.init()...");
          Serial.flush();
        #endif
        // Tab variant (BLACKTAB) comes from TFT_eSPI User_Setup — see boards/esp32c3-minitv/ST7735_setup.h
        tft.init();
        #if defined(SERIAL_PRINTING)
          Serial.println("LCD: init OK");
          Serial.flush();
        #endif
        tft.setRotation(tft_rotation);
        st7735_clear_screen();
        pinMode(TFT_BUTTON_PIN, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(TFT_BUTTON_PIN), buttonISR, FALLING);
      #endif

      #if defined(DISPLAY_GC9A01)
        #if defined(SERIAL_PRINTING)
          Serial.println("LCD: SPI (pins 6,7)...");
          Serial.flush();
        #endif
        SPI.begin(6, -1, 7, -1);
        #if defined(SERIAL_PRINTING)
          Serial.println("LCD: tft.init()...");
          Serial.flush();
        #endif
        tft.init();
        #if defined(SERIAL_PRINTING)
          Serial.println("LCD: init OK");
          Serial.flush();
        #endif
        tft.setRotation(tft_rotation);
        gc9a01_clear_screen();
        touch_setup_gc9a01();
        pinMode(TFT_BL, OUTPUT);
        digitalWrite(TFT_BL, HIGH);
        pinMode(TFT_BUTTON_PIN, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(TFT_BUTTON_PIN), buttonISR, FALLING);
      #endif
    }


    void display_boot() {
      // Abstraction layer: compilation time, features, etc.

      #if defined(DISPLAY_ST7735)
          st7735_clear_screen();
          tft_layout_drawn = false;
          // Board + frequency
          tft.setTextColor(DUCO_GOLD, BLACK);
          tft.setTextSize(2);
          tft.setCursor(4, 6);
          tft.print("ESP32-C3");
          tft.setTextColor(WHITE, BLACK);
          tft.setTextSize(1);
          tft.setCursor(4, 28);
          tft.print(String(getCpuFrequencyMhz()).c_str());
          tft.print(" MHz");
          tft.drawFastHLine(4, 40, 120, DUCO_DARK);
          // Compile date
          tft.setTextColor(DUCO_GRAY, BLACK);
          tft.setCursor(4, 46);
          tft.print("Built ");
          tft.print(__DATE__);
          // Features
          tft.setTextColor(DUCO_CYAN, BLACK);
          tft.setCursor(4, 62);
          tft.print("Features:");
          tft.setTextColor(WHITE, BLACK);
          tft.setCursor(4, 74);
          String f7735 = "OTA ";
          #if defined(SERIAL_PRINTING)
            f7735 += "Serial ";
          #endif
          #if defined(WEB_DASHBOARD)
            f7735 += "Web ";
          #endif
          f7735 += "ST7735";
          tft.print(f7735);
      #endif

      #if defined(DISPLAY_GC9A01)
        gc9a01_clear_screen();
        tft_layout_drawn = false;
        tft.setTextColor(DUCO_GOLD, BLACK);
        tft.setTextSize(2);
        tft.setCursor(GC9A01_SX(4), GC9A01_SY(6));
        tft.print("ESP32-C3");
        tft.setTextColor(WHITE, BLACK);
        tft.setTextSize(1);
        tft.setCursor(GC9A01_SX(4), GC9A01_SY(28));
        tft.print(String(getCpuFrequencyMhz()).c_str());
        tft.print(" MHz");
        tft.drawFastHLine(GC9A01_SX(4), GC9A01_SY(40), GC9A01_W - 8, DUCO_DARK);
        tft.setTextColor(DUCO_GRAY, BLACK);
        tft.setCursor(GC9A01_SX(4), GC9A01_SY(46));
        tft.print("Built ");
        tft.print(__DATE__);
        tft.setTextColor(DUCO_CYAN, BLACK);
        tft.setCursor(GC9A01_SX(4), GC9A01_SY(62));
        tft.print("Features:");
        tft.setTextColor(WHITE, BLACK);
        tft.setCursor(GC9A01_SX(4), GC9A01_SY(74));
        String fgc9 = "OTA ";
        #if defined(SERIAL_PRINTING)
          fgc9 += "Serial ";
        #endif
        #if defined(WEB_DASHBOARD)
          fgc9 += "Web ";
        #endif
        fgc9 += "GC9A01";
        #if defined(TOUCH_CST816D)
          fgc9 += " Touch";
        #endif
        tft.print(fgc9);
      #endif

      #if defined(DISPLAY_16X2)
          lcd.clear();
          #if defined(ESP8266)
            lcd.print("ESP8266 ");
          #elif defined(CONFIG_FREERTOS_UNICORE)
            lcd.print("ESP32S2 ");
          #else
            lcd.print("ESP32 ");
          #endif
          #if defined(ESP8266)
            lcd.print(String(ESP.getCpuFreqMHz()).c_str());
          #else
            lcd.print(String(getCpuFrequencyMhz()).c_str());
          #endif
          lcd.print(" MHz");

          lcd.setCursor(0, 1);
          lcd.print(__DATE__);
      #endif

      #if defined(DISPLAY_SSD1306)
          u8g2.clearBuffer();
          
          u8g2.setFont(u8g2_font_profont15_tr);
          u8g2.setCursor(2, 13);
          #if defined(ESP8266)
            u8g2.print("ESP8266 ");
          #elif defined(CONFIG_FREERTOS_UNICORE)
            u8g2.print("ESP32S2/C3 ");
          #else
            u8g2.print("ESP32 ");
          #endif
  
          #if defined(ESP8266)
            u8g2.print(String(ESP.getCpuFreqMHz()).c_str());
          #else
            u8g2.print(String(getCpuFrequencyMhz()).c_str());
          #endif
          u8g2.print(" MHz");
  
          u8g2.setFont(u8g2_font_profont10_tr);
          u8g2.drawLine(1, 27, 126, 27);
          u8g2.setCursor(2, 24);
          u8g2.print("Compiled ");
          u8g2.print(__DATE__);
          
          
          u8g2.drawStr(2, 37, "Features:");
          u8g2.setCursor(2, 46);
          String features_str = "OTA ";
          #if defined(USE_LAN)
            features_str += "LAN ";
          #endif
          #if defined(LED_BLINKING)
            features_str += "Blink ";
          #endif
          #if defined(SERIAL_PRINTING)
            features_str += "Serial ";
          #endif
          #if defined(WEB_DASHBOARD)
            features_str += "Webserver ";
          #endif
          #if defined(DISPLAY_16X2)
            features_str += "LCD16X2 ";
          #endif
          #if defined(DISPLAY_SSD1306)
            features_str += "SSD1306 ";
          #endif
          #if defined(USE_INTERNAL_SENSOR)
            features_str += "Int. sensor ";
          #endif
          #if defined(USE_DS18B20)
            features_str += "DS18B20 ";
          #endif
          #if defined(USE_DHT)
            features_str += "DHT ";
          #endif
          #if defined(USE_HSU07M)
            features_str += "HSU07M ";
          #endif
          drawStrMultiline(features_str.c_str(), 2, 46);
          u8g2.sendBuffer();
      #endif

      #if defined(DISPLAY_ST7789)
          tft.fillScreen(BLACK);
          tft_layout_drawn = false;
          int sw = tft.width();
          bool landscape = isLandscape();

          // Board type + frequency
          tft.setTextColor(DUCO_GOLD, BLACK);
          tft.setTextSize(landscape ? 3 : 2);
          tft.setCursor(10, 15);
          #if defined(ESP8266)
            tft.print("ESP8266 ");
          #elif defined(CONFIG_FREERTOS_UNICORE)
            tft.print("ESP32S2/C3 ");
          #else
            tft.print("ESP32 ");
          #endif
          #if defined(ESP8266)
            tft.print(String(ESP.getCpuFreqMHz()).c_str());
          #else
            tft.print(String(getCpuFrequencyMhz()).c_str());
          #endif
          tft.print(" MHz");

          // Separator
          tft.drawFastHLine(10, landscape ? 50 : 45, sw - 20, DUCO_DARK);

          // Compile date
          tft.setTextColor(WHITE, BLACK);
          tft.setTextSize(landscape ? 2 : 1);
          tft.setCursor(10, landscape ? 60 : 55);
          tft.print("Compiled ");
          tft.print(__DATE__);

          // Features
          tft.setTextColor(DUCO_CYAN, BLACK);
          tft.setTextSize(landscape ? 2 : 1);
          tft.setCursor(10, landscape ? 90 : 75);
          tft.print("Features:");
          tft.setTextColor(WHITE, BLACK);
          tft.setTextSize(1);
          tft.setCursor(10, landscape ? 115 : 95);
          String features_str = "OTA ";
          #if defined(USE_LAN)
            features_str += "LAN ";
          #endif
          #if defined(LED_BLINKING)
            features_str += "Blink ";
          #endif
          #if defined(SERIAL_PRINTING)
            features_str += "Serial ";
          #endif
          #if defined(WEB_DASHBOARD)
            features_str += "Webserver ";
          #endif
          #if defined(DISPLAY_ST7789)
            features_str += "ST7789 ";
          #endif
          #if defined(USE_INTERNAL_SENSOR)
            features_str += "Int.sensor ";
          #endif
          #if defined(USE_DS18B20)
            features_str += "DS18B20 ";
          #endif
          #if defined(USE_DHT)
            features_str += "DHT ";
          #endif
          #if defined(USE_HSU07M)
            features_str += "HSU07M ";
          #endif
          tft.print(features_str);
      #endif
    }

    void display_info(String message) {
      // Abstraction layer: info screens (setups)

      #if defined(DISPLAY_ST7735)
          st7735_clear_screen();
          tft_layout_drawn = false;
          // Title
          tft.setTextColor(DUCO_GOLD, BLACK);
          tft.setTextSize(2);
          tft.setCursor(4, 10);
          tft.print("Duino");
          tft.setCursor(4, 30);
          tft.print("Coin");
          // MINER + version
          tft.setTextColor(WHITE, BLACK);
          tft.setTextSize(1);
          tft.setCursor(4, 52);
          tft.print("MINER  v");
          tft.print(String(SOFTWARE_VERSION).c_str());
          tft.setTextColor(DUCO_GRAY, BLACK);
          tft.setCursor(4, 64);
          tft.print("duinocoin.com");
          tft.drawFastHLine(4, 78, 120, DUCO_DARK);
          // Status message (wraps if long)
          tft.setTextColor(DUCO_CYAN, BLACK);
          tft.setTextSize(1);
          tft.setCursor(4, 88);
          tft.print(message);
      #endif

      #if defined(DISPLAY_GC9A01)
          gc9a01_clear_screen();
          tft_layout_drawn = false;
          tft.setTextColor(DUCO_GOLD, BLACK);
          tft.setTextSize(2);
          tft.setCursor(GC9A01_SX(4), GC9A01_SY(10));
          tft.print("Duino");
          tft.setCursor(GC9A01_SX(4), GC9A01_SY(30));
          tft.print("Coin");
          tft.setTextColor(WHITE, BLACK);
          tft.setTextSize(1);
          tft.setCursor(GC9A01_SX(4), GC9A01_SY(52));
          tft.print("MINER  v");
          tft.print(String(SOFTWARE_VERSION).c_str());
          tft.setTextColor(DUCO_GRAY, BLACK);
          tft.setCursor(GC9A01_SX(4), GC9A01_SY(64));
          tft.print("duinocoin.com");
          tft.drawFastHLine(GC9A01_SX(4), GC9A01_SY(78), GC9A01_W - 8, DUCO_DARK);
          tft.setTextColor(DUCO_CYAN, BLACK);
          tft.setTextSize(1);
          tft.setCursor(GC9A01_SX(4), GC9A01_SY(88));
          tft.print(message);
      #endif

      #if defined(DISPLAY_SSD1306)
          u8g2.clearBuffer();
          u8g2.drawXBMP(-1, 3, 41, 45, image_duco_logo_big_bits);
          u8g2.setFont(u8g2_font_t0_16b_tr);
          #if defined(ESP8266)
              u8g2.drawStr(42, 27, "ESP8266");
          #elif defined(CONFIG_FREERTOS_UNICORE)
              u8g2.drawStr(42, 27, "ESP32S2/C3");
          #else
              u8g2.drawStr(42, 27, "ESP32");
          #endif
          u8g2.setFont(u8g2_font_t0_13b_tr);
          u8g2.drawStr(41, 14, "Duino-Coin");
          u8g2.setFont(u8g2_font_6x10_tr);
          u8g2.drawStr(98, 36, "MINER");
          u8g2.setFont(u8g2_font_6x13_tr);
          u8g2.drawStr(1, 60, message.c_str());
          u8g2.setFont(u8g2_font_5x8_tr);
          u8g2.drawStr(42, 46, "www.duinocoin.com");
          u8g2.setFont(u8g2_font_4x6_tr);
          u8g2.drawStr(116, 14, String(SOFTWARE_VERSION).c_str());
          u8g2.sendBuffer();
      #endif

      #if defined(DISPLAY_16X2)
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.write(0);
          lcd.print(" Duino-Coin ");
          lcd.print(SOFTWARE_VERSION);
          lcd.setCursor(0, 1);
          lcd.print(message);
      #endif

      #if defined(DISPLAY_ST7789)
          tft.fillScreen(BLACK);
          tft_layout_drawn = false;
          int sw = tft.width();
          bool landscape = isLandscape();
          int sh = tft.height();

          // Duino-Coin title
          tft.setTextColor(DUCO_GOLD, BLACK);
          tft.setTextSize(landscape ? 3 : 2);
          tft.setCursor(landscape ? 50 : 10, 10);
          tft.print("Duino-Coin");

          // Board type
          tft.setTextColor(WHITE, BLACK);
          tft.setTextSize(landscape ? 3 : 2);
          tft.setCursor(landscape ? 50 : 10, landscape ? 45 : 40);
          #if defined(ESP8266)
            tft.print("ESP8266");
          #elif defined(CONFIG_FREERTOS_UNICORE)
            tft.print("ESP32S2/C3");
          #else
            tft.print("ESP32");
          #endif

          // MINER label
          tft.setTextColor(DUCO_GOLD, BLACK);
          tft.setTextSize(2);
          tft.setCursor(landscape ? 230 : 100, landscape ? 50 : 45);
          tft.print("MINER");

          // Version
          tft.setTextSize(1);
          tft.setTextColor(DUCO_GRAY, BLACK);
          tft.setCursor(landscape ? 280 : 10, landscape ? 70 : 70);
          tft.print("v");
          tft.print(String(SOFTWARE_VERSION).c_str());

          // URL
          tft.setTextColor(DUCO_GRAY, BLACK);
          tft.setTextSize(1);
          tft.setCursor(landscape ? 50 : 10, landscape ? 85 : 85);
          tft.print("www.duinocoin.com");

          // Message
          tft.setTextColor(WHITE, BLACK);
          tft.setTextSize(2);
          tft.setCursor(10, landscape ? 130 : 110);
          tft.print(message);
      #endif
    }


    void display_mining_results(String hashrate, String accepted_shares, String total_shares, String uptime, String node, 
                                String difficulty, String sharerate, String ping, String accept_rate) {
      // Ran after each found share
      // Abstraction layer: displaying mining results

      #if defined(DISPLAY_ST7735)
          if (tft_busy) return;
          tft_busy = true;

          checkButton();
          if (!tft_layout_drawn) drawStaticLayout();

          float hr = hashrate.toFloat();

          // === TOP BAR (y 0..24) ===
          tft.fillRect(0, 0, 128, 25, BLACK);
          drawWifiBars(0, 10);
          tft.setTextColor(WHITE, BLACK);
          tft.setTextSize(1);
          tft.setCursor(20, 13);
          tft.print(st7735_fit(ping + "ms", 5));
          tft.setTextColor(DUCO_GRAY, BLACK);
          tft.setCursor(50, 13);
          tft.print(st7735_fit(node, 10));

          // === HASHRATE (y 26..65) ===
          tft.fillRect(0, 26, 128, 40, BLACK);
          tft.setTextColor(DUCO_GREEN, BLACK);
          if (hr < 10.0) {
            tft.setTextSize(4);
            tft.setCursor(6, 30);
          } else if (hr < 100.0) {
            tft.setTextSize(3);
            tft.setCursor(6, 35);
          } else {
            tft.setTextSize(2);
            tft.setCursor(6, 38);
          }
          tft.print(hashrate);
          tft.setTextColor(DUCO_GRAY, BLACK);
          tft.setTextSize(1);
          tft.setCursor(94, 54);
          tft.print("kH/s");

          // === STATS (y 67..95) ===
          tft.fillRect(0, 67, 128, 29, BLACK);
          tft.setTextColor(WHITE, BLACK);
          tft.setTextSize(1);
          tft.setCursor(2, 74);
          tft.print(st7735_fit(difficulty, 8));
          tft.setCursor(2, 86);
          tft.print(st7735_fit(sharerate, 8));
          tft.setTextColor(DUCO_GRAY, BLACK);
          tft.setCursor(70, 74);
          tft.print("diff");
          tft.setCursor(70, 86);
          tft.print("sh/s");

          // === SHARES (y 97..115) ===
          tft.fillRect(0, 97, 128, 20, BLACK);
          drawCheckmark(1, 101);
          tft.setTextColor(WHITE, BLACK);
          tft.setTextSize(1);
          tft.setCursor(14, 103);
          tft.print(st7735_fit(accepted_shares + "/" + total_shares, 9));
          tft.setTextColor(DUCO_CYAN, BLACK);
          tft.setCursor(84, 103);
          tft.print(st7735_fit(st7735_pct(accept_rate), 6));

          // === FOOTER (y 117..127) ===
          tft.fillRect(0, 117, 128, 11, BLACK);
          tft.setTextSize(1);
          tft.setTextColor(DUCO_GRAY, BLACK);
          tft.setCursor(2, 119);
          tft.print(st7735_fit(WiFi.localIP().toString(), 15));
          tft.setTextColor(WHITE, BLACK);
          st7735_print_right(st7735_fit(uptime, 9), 119);

          tft_busy = false;
      #endif

      #if defined(DISPLAY_GC9A01)
          if (tft_busy) return;
          tft_busy = true;

          checkTouch();
          checkButton();
          if (!tft_layout_drawn) drawStaticLayout();

          float hr = hashrate.toFloat();

          tft.fillRect(GC9A01_MX, GC9A01_MY, GC9A01_W, GC9A01_SY(25) - GC9A01_MY, BLACK);
          drawWifiBars(GC9A01_MX, GC9A01_SY(10));
          tft.setTextColor(WHITE, BLACK);
          tft.setTextSize(1);
          tft.setCursor(GC9A01_SX(20), GC9A01_SY(13));
          tft.print(gc9a01_fit(ping + "ms", 5));
          tft.setTextColor(DUCO_GRAY, BLACK);
          tft.setCursor(GC9A01_SX(50), GC9A01_SY(13));
          tft.print(gc9a01_fit(node, 10));

          tft.fillRect(GC9A01_MX, GC9A01_SY(26), GC9A01_W, GC9A01_SY(65) - GC9A01_SY(26), BLACK);
          tft.setTextColor(DUCO_GREEN, BLACK);
          if (hr < 10.0) {
            tft.setTextSize(4);
            tft.setCursor(GC9A01_SX(6), GC9A01_SY(30));
          } else if (hr < 100.0) {
            tft.setTextSize(3);
            tft.setCursor(GC9A01_SX(6), GC9A01_SY(35));
          } else {
            tft.setTextSize(2);
            tft.setCursor(GC9A01_SX(6), GC9A01_SY(38));
          }
          tft.print(hashrate);
          tft.setTextColor(DUCO_GRAY, BLACK);
          tft.setTextSize(1);
          tft.setCursor(GC9A01_SX(94), GC9A01_SY(54));
          tft.print("kH/s");

          tft.fillRect(GC9A01_MX, GC9A01_SY(67), GC9A01_W, GC9A01_SY(95) - GC9A01_SY(67), BLACK);
          tft.setTextColor(WHITE, BLACK);
          tft.setTextSize(1);
          tft.setCursor(GC9A01_SX(2), GC9A01_SY(74));
          tft.print(gc9a01_fit(difficulty, 8));
          tft.setCursor(GC9A01_SX(2), GC9A01_SY(86));
          tft.print(gc9a01_fit(sharerate, 8));
          tft.setTextColor(DUCO_GRAY, BLACK);
          tft.setCursor(GC9A01_SX(70), GC9A01_SY(74));
          tft.print("diff");
          tft.setCursor(GC9A01_SX(70), GC9A01_SY(86));
          tft.print("sh/s");

          tft.fillRect(GC9A01_MX, GC9A01_SY(97), GC9A01_W, GC9A01_SY(115) - GC9A01_SY(97), BLACK);
          drawCheckmark(GC9A01_SX(1), GC9A01_SY(101));
          tft.setTextColor(WHITE, BLACK);
          tft.setTextSize(1);
          tft.setCursor(GC9A01_SX(14), GC9A01_SY(103));
          tft.print(gc9a01_fit(accepted_shares + "/" + total_shares, 9));
          tft.setTextColor(DUCO_CYAN, BLACK);
          tft.setCursor(GC9A01_SX(84), GC9A01_SY(103));
          tft.print(gc9a01_fit(gc9a01_pct(accept_rate), 6));

          tft.fillRect(GC9A01_MX, GC9A01_SY(117), GC9A01_W, GC9A01_SY(127) - GC9A01_SY(117) + 8, BLACK);
          tft.setTextSize(1);
          tft.setTextColor(DUCO_GRAY, BLACK);
          tft.setCursor(GC9A01_SX(2), GC9A01_SY(119));
          tft.print(gc9a01_fit(WiFi.localIP().toString(), 15));
          tft.setTextColor(WHITE, BLACK);
          gc9a01_print_right(gc9a01_fit(uptime, 9), GC9A01_SY(119));

          tft.fillRect(GC9A01_MX, GC9A01_SY(25),  GC9A01_W, 1, DUCO_DARK);
          tft.fillRect(GC9A01_MX, GC9A01_SY(66),  GC9A01_W, 1, DUCO_DARK);
          tft.fillRect(GC9A01_MX, GC9A01_SY(96),  GC9A01_W, 1, DUCO_DARK);
          tft.fillRect(GC9A01_MX, GC9A01_SY(116), GC9A01_W, 1, DUCO_DARK);

          tft_busy = false;
      #endif

      #if defined(DISPLAY_SSD1306)
          u8g2.clearBuffer();
          u8g2.setFont(u8g2_font_profont10_tr);
          u8g2.drawStr(67, 26, "kH");
          if (hashrate.toFloat() < 100.0) {
            u8g2.setFont(u8g2_font_profont29_tr);
            u8g2.drawStr(2, 36, hashrate.c_str());
          } else {
            u8g2.setFont(u8g2_font_profont22_tr);
            u8g2.drawStr(3, 35, hashrate.c_str());
          }

          u8g2.setFont(u8g2_font_haxrcorp4089_tr);
          u8g2.drawStr(52, 12, node.c_str());

          u8g2.setFont(u8g2_font_t0_11_tr);
          u8g2.drawStr(17, 47, (accepted_shares + "/" + total_shares).c_str());
          u8g2.setFont(u8g2_font_5x7_tr);
          u8g2.drawStr(88, 47, ("(" + accept_rate + "%)").c_str());

          u8g2.setFont(u8g2_font_profont12_tr);
          u8g2.drawStr(20, 12, (ping + "ms").c_str());
          u8g2.drawStr(69, 36, "s");

          u8g2.setFont(u8g2_font_6x13_tr);
          u8g2.drawStr(125-u8g2.getStrWidth(uptime.c_str()), 61, uptime.c_str());

          u8g2.drawStr(85, 38, sharerate.c_str());
          u8g2.drawStr(85, 27, difficulty.c_str());
          u8g2.drawLine(67, 28, 75, 28);

          u8g2.drawXBMP(2, 38, 13, 10, image_check_contour_bits);

          if (WiFi.RSSI() > -40) {
            u8g2.drawXBMP(1, 0, 15, 16, image_network_4_bars_bits);
          } else if (WiFi.RSSI() > -60) {
            u8g2.drawXBMP(1, 0, 15, 16, image_network_3_bars_bits);
          } else if (WiFi.RSSI() > -75) {
            u8g2.drawXBMP(1, 0, 15, 16, image_network_2_bars_bits);
          } else {
            u8g2.drawXBMP(1, 0, 15, 16, image_network_1_bar_bits);
          }

          u8g2.setFont(u8g2_font_4x6_tr);
          u8g2.drawStr(14, 61, String(WiFi.localIP().toString()).c_str());
          u8g2.drawStr(14, 55, ("Duino-Coin " + String(SOFTWARE_VERSION)).c_str());
          u8g2.drawXBMP(2, 11, 9, 50, image_duco_logo_bits);
          u8g2.drawStr(111, 27, "diff");
          u8g2.drawStr(107, 38, "shr/s");

          u8g2.sendBuffer();
      #endif

      #if defined(DISPLAY_16X2)
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(hashrate);
          lcd.setCursor(4,0);
          lcd.write(2); // kh

          lcd.setCursor(7, 0);
          lcd.print(difficulty);
          lcd.print(" diff");

          lcd.setCursor(0, 1);
          lcd.write(1); // checkmark
          lcd.print(accepted_shares);

          lcd.setCursor(7, 1);
          lcd.print(ping);
          lcd.write(3); // ms

          lcd.setCursor(12, 1);
          lcd.print(sharerate);
          lcd.print("s");
      #endif

      #if defined(DISPLAY_ST7789)
          // Prevent concurrent access from both cores
          if (tft_busy) return;
          tft_busy = true;

          // Check for rotation button press
          checkButton();

          // Draw static layout elements once (separators, labels)
          if (!tft_layout_drawn) {
            drawStaticLayout();
          }

          if (isLandscape()) {
            // ========== LANDSCAPE 320x170 ==========
            // === TOP BAR ===
            drawWifiBars(5, 3);
            tft.setTextColor(WHITE, BLACK);
            tft.setTextSize(2);
            tft.setCursor(45, 6);
            tft.print(ping + "ms   ");
            tft.setTextSize(1);
            tft.setTextColor(DUCO_GRAY, BLACK);
            tft.setCursor(140, 10);
            tft.print(node + "   ");

            // === HASHRATE ===
            tft.fillRect(5, 35, 125, 40, BLACK);
            tft.setTextColor(DUCO_GREEN, BLACK);
            if (hashrate.toFloat() < 100.0) {
              tft.setTextSize(4);
              tft.setCursor(5, 40);
            } else {
              tft.setTextSize(3);
              tft.setCursor(5, 45);
            }
            tft.print(hashrate);
            // kH/s label redrawn every cycle (prevents it from being erased)
            tft.setTextColor(DUCO_GRAY, BLACK);
            tft.setTextSize(2);
            tft.setCursor(135, 45);
            tft.print("kH/s");

            // === DIFF + SHARERATE ===
            tft.fillRect(205, 35, 70, 16, BLACK);
            tft.fillRect(205, 62, 70, 16, BLACK);
            tft.setTextColor(WHITE, BLACK);
            tft.setTextSize(2);
            tft.setCursor(210, 35);
            tft.print(difficulty);
            tft.setCursor(210, 62);
            tft.print(sharerate);

            // === SHARES ===
            tft.fillRect(3, 110, 20, 18, BLACK);
            drawCheckmark(5, 112);
            tft.setTextColor(WHITE, BLACK);
            tft.setTextSize(2);
            tft.setCursor(28, 112);
            tft.print(accepted_shares + "/" + total_shares + "  ");
            tft.setTextSize(1);
            tft.setTextColor(DUCO_CYAN, BLACK);
            tft.setCursor(215, 118);
            tft.print("(" + accept_rate + "%)  ");

            // === BOTTOM ===
            tft.setTextSize(1);
            tft.setTextColor(DUCO_GRAY, BLACK);
            tft.setCursor(5, 158);
            tft.print(WiFi.localIP().toString() + "   ");
            tft.fillRect(160, 145, 160, 20, BLACK);
            tft.setTextColor(WHITE, BLACK);
            tft.setTextSize(2);
            int uptimeW = uptime.length() * 12;
            tft.setCursor(315 - uptimeW, 148);
            tft.print(uptime);

          } else {
            // ========== PORTRAIT 170x320 ==========
            // === TOP BAR (0..27) ===
            drawWifiBars(5, 3);
            tft.setTextColor(WHITE, BLACK);
            tft.setTextSize(2);
            tft.setCursor(45, 6);
            tft.print(ping + "ms  ");
            // Node doesn't fit well on top bar in portrait, skip or shrink

            // === HASHRATE (30..129) ===
            tft.fillRect(5, 35, 160, 60, BLACK);
            tft.setTextColor(DUCO_GREEN, BLACK);
            if (hashrate.toFloat() < 100.0) {
              tft.setTextSize(5);
              tft.setCursor(10, 42);
            } else {
              tft.setTextSize(4);
              tft.setCursor(10, 48);
            }
            tft.print(hashrate);

            // === STATS (132..194) ===
            tft.fillRect(5, 135, 90, 20, BLACK);
            tft.setTextColor(WHITE, BLACK);
            tft.setTextSize(2);
            tft.setCursor(5, 138);
            tft.print(difficulty);
            tft.setTextSize(1);
            tft.setTextColor(DUCO_GRAY, BLACK);
            tft.setCursor(100, 143);
            tft.print("diff");

            tft.fillRect(5, 162, 90, 20, BLACK);
            tft.setTextColor(WHITE, BLACK);
            tft.setTextSize(2);
            tft.setCursor(5, 165);
            tft.print(sharerate);
            tft.setTextSize(1);
            tft.setTextColor(DUCO_GRAY, BLACK);
            tft.setCursor(100, 170);
            tft.print("shr/s");

            // === SHARES (197..254) ===
            tft.fillRect(3, 202, 20, 18, BLACK);
            drawCheckmark(5, 204);
            tft.setTextColor(WHITE, BLACK);
            tft.setTextSize(2);
            tft.setCursor(28, 204);
            tft.print(accepted_shares + "/" + total_shares + "  ");
            tft.setTextSize(1);
            tft.setTextColor(DUCO_CYAN, BLACK);
            tft.setCursor(28, 228);
            tft.print("(" + accept_rate + "%)  ");

            // Node name
            tft.setTextColor(DUCO_GRAY, BLACK);
            tft.setTextSize(1);
            tft.setCursor(5, 243);
            tft.print(node + "   ");

            // === BOTTOM (257..320) ===
            tft.setTextSize(1);
            tft.setTextColor(DUCO_GRAY, BLACK);
            tft.setCursor(5, 275);
            tft.print(WiFi.localIP().toString() + "   ");

            tft.fillRect(0, 290, 170, 25, BLACK);
            tft.setTextColor(WHITE, BLACK);
            tft.setTextSize(2);
            int uptimeW = uptime.length() * 12;
            tft.setCursor(165 - uptimeW, 295);
            tft.print(uptime);
          }

          tft_busy = false;
      #endif
    }

    void display_input_poll() {
      #if defined(TOUCH_CST816D)
        checkTouch();
      #endif
      #if defined(DISPLAY_ST7789) || defined(DISPLAY_ST7735) || defined(DISPLAY_GC9A01)
        checkButton();
      #endif
    }
#endif

#endif
