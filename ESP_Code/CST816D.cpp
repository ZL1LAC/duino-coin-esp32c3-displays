#include "CST816D.h"

CST816D::CST816D(int8_t sda_pin, int8_t scl_pin, int8_t rst_pin, int8_t int_pin) {
    _sda = sda_pin;
    _scl = scl_pin;
    _rst = rst_pin;
    _int = int_pin;
}

void CST816D::begin(void) {
    if (_sda != -1 && _scl != -1) {
        Wire.begin(_sda, _scl);
        Wire.setClock(400000);
    } else {
        Wire.begin();
        Wire.setClock(400000);
    }

    // Factory demo pulses INT low briefly (not INPUT_PULLUP)
    if (_int != -1) {
        pinMode(_int, OUTPUT);
        digitalWrite(_int, HIGH);
        delay(1);
        digitalWrite(_int, LOW);
        delay(1);
    }

    if (_rst != -1) {
        pinMode(_rst, OUTPUT);
        digitalWrite(_rst, LOW);
        delay(10);
        digitalWrite(_rst, HIGH);
        delay(300);
    }

    i2c_write(0xFE, 0xFF);

    if (_int != -1) {
        pinMode(_int, INPUT);
    }
}

bool CST816D::getTouch(uint16_t *x, uint16_t *y, uint8_t *gesture) {
    bool fingerDown = (bool)i2c_read(0x02);

    *gesture = i2c_read(0x01);

    uint8_t data[4];
    i2c_read_continuous(0x03, data, 4);
    *x = ((data[0] & 0x0f) << 8) | data[1];
    *y = ((data[2] & 0x0f) << 8) | data[3];

    return fingerDown;
}

uint8_t CST816D::i2c_read(uint8_t addr) {
    uint8_t rdData = 0;
    uint8_t rdDataCount = 0;
    uint8_t tries = 0;
    do {
        Wire.beginTransmission(I2C_ADDR_CST816D);
        Wire.write(addr);
        Wire.endTransmission(false);
        rdDataCount = Wire.requestFrom(I2C_ADDR_CST816D, 1);
        tries++;
    } while (rdDataCount == 0 && tries < 8);
    while (Wire.available()) {
        rdData = Wire.read();
    }
    return rdData;
}

uint8_t CST816D::i2c_read_continuous(uint8_t addr, uint8_t *data, uint32_t length) {
    Wire.beginTransmission(I2C_ADDR_CST816D);
    Wire.write(addr);
    if (Wire.endTransmission(true)) {
        return (uint8_t)-1;
    }
    Wire.requestFrom(I2C_ADDR_CST816D, length);
    for (uint32_t i = 0; i < length; i++) {
        *data++ = Wire.read();
    }
    return 0;
}

void CST816D::i2c_write(uint8_t addr, uint8_t data) {
    Wire.beginTransmission(I2C_ADDR_CST816D);
    Wire.write(addr);
    Wire.write(data);
    Wire.endTransmission();
}
