// Heltec WiFi LoRa 32 (V2) — onboard 128×64 SSD1306 OLED
// Vext (GPIO21) powers the OLED rail. OLED I2C: SDA=4, SCL=15, RST=16.
// Use U8g2 SW_I2C (not HW_I2C) — Heltec's variant defines SDA/SCL as 21/22 which
// conflicts with Vext and breaks Wire.begin() without explicit pins.
#ifndef HELTEC_DISPLAY_H
#define HELTEC_DISPLAY_H

#include <Arduino.h>

#ifndef HELTEC_VEXT_PIN
  #define HELTEC_VEXT_PIN 21
#endif
#ifndef HELTEC_OLED_RST
  #define HELTEC_OLED_RST 16
#endif
#ifndef HELTEC_OLED_SDA
  #define HELTEC_OLED_SDA 4
#endif
#ifndef HELTEC_OLED_SCL
  #define HELTEC_OLED_SCL 15
#endif

inline void heltec_vext_on() {
  pinMode(HELTEC_VEXT_PIN, OUTPUT);
  digitalWrite(HELTEC_VEXT_PIN, LOW);  // LOW = Vext rail ON (Heltec V2)
}

inline void heltec_oled_reset() {
  pinMode(HELTEC_OLED_RST, OUTPUT);
  digitalWrite(HELTEC_OLED_RST, LOW);
  delay(50);
  digitalWrite(HELTEC_OLED_RST, HIGH);
  delay(50);
}

// Call as early as possible in setup() — before Serial or any Wire user.
inline void heltec_board_early_init() {
  heltec_vext_on();
  delay(100);
  heltec_oled_reset();
}

template<typename U8G2>
inline void heltec_display_init(U8G2 &u8g2) {
  heltec_board_early_init();
  u8g2.begin();
  u8g2.setBusClock(400000);
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  u8g2.sendBuffer();
}

#endif
