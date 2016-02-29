#include <i2cbase.h>
#include <stdint.h>

class adc128d818 : public i2cBase {
 public:
  adc128d818(const uint8_t dev_addr)
    : i2cBase(dev_addr) {}
  void Init();
  uint16_t RawValue(const uint8_t channel);
 private:
   void pollUntilReady();
};
