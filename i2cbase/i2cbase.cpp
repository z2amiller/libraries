#include "i2cbase.h"
#include <Wire.h>

void i2cBase::write8(const uint8_t addr, const uint8_t data) {
  Wire.beginTransmission(i2c_addr_);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission();
}

uint8_t i2cBase::read8(const uint8_t addr) {
  Wire.beginTransmission(i2c_addr_);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.beginTransmission(i2c_addr_);
  Wire.requestFrom(i2c_addr_, (uint8_t)1);
  const uint8_t ret = Wire.read();
  Wire.endTransmission();
  return ret;
}

uint16_t i2cBase::read16(const uint8_t addr) {
  Wire.beginTransmission(i2c_addr_);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.beginTransmission(i2c_addr_);
  Wire.requestFrom(i2c_addr_, (uint8_t)2);
  uint16_t ret = Wire.read();
  ret <<= 8;
  ret |= Wire.read();
  Wire.endTransmission();
  return ret;
}

uint32_t i2cBase::read24(const uint8_t addr) {
  Wire.beginTransmission(i2c_addr_);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.beginTransmission(i2c_addr_);
  Wire.requestFrom(i2c_addr_, (uint8_t)3);
  uint32_t ret = Wire.read();
  ret <<= 8;
  ret |= Wire.read();
  ret <<= 8;
  ret |= Wire.read();
  Wire.endTransmission();
  return ret;
}

