#include "Arduino.h"

class i2cBase {
 public:
  // i2cbase targets an i2c device at this address.
  // i2cbase expects the Wire library to be initialized,
  // i.e. Wire.begin() or Wire.begin(SDAPIN, SCLPIN).
  i2cBase(const uint8_t dev_addr)
    : i2c_addr_(dev_addr) {}

  virtual void Init() {};

 protected:
  uint8_t read8(const uint8_t addr);
  int8_t readS8(const uint8_t addr) {
    return (int8_t)read8(addr);
  }

  uint16_t read16(const uint8_t addr);
  int16_t readS16(const uint8_t addr) {
    return (int16_t)read16(addr);
  }
  uint16_t read16LE(const uint8_t addr) {
    const uint16_t t = read16(addr);
    return (t >> 8) | (t << 8);
  }
  int16_t readS16LE(const uint8_t addr) {
    return (int16_t)read16LE(addr);
  }
  unit32_t read24(const uint8_t addr);

  void write8(const uint8_t addr, const uint8_t data);

 private:
  uint8_t i2c_addr_;
};
