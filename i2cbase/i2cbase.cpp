#include <Wire.h>

i2cBase::i2cBase(const uint8_t dev_addr,
                 const uint8_t sda,
                 const uint8_t scl)
    : i2c_addr_(dev_addr),
      sda_pin_(sda),
      scl_pin_(scl) {}

i2cBase::Init() {
  Wire.begin(sda_pin_, scl_pin_);
}

void i2cBase::write8(const uint8_t addr, const uint8_t data) {
  Wire.beginTransmission(adc_addr_);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission();
}

uint8_t i2cBase::read8(const uint8_t addr) {
  Wire.beginTransmission(adc_addr_);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.beginTransmission(adc_addr_);
  Wire.requestFrom(adc_addr_, (uint8_t)1);
  const uint8_t ret = Wire.read();
  Wire.endTransmission();
  return ret;
}

uint16_t i2cBase::read16(const uint8_t addr) {
  Wire.beginTransmission(adc_addr_);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.beginTransmission(adc_addr_);
  Wire.requestFrom(adc_addr_, (uint8_t)2);
  uint16_t ret = Wire.read();
  ret <<= 8;
  ret |= Wire.read();
  Wire.endTransmission();
  return ret;
}
