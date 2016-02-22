#include <i2cbase.h>

public class adc128d818 : public i2cBase {
 public:
  adc128d818(const uint8_t dev_addr,
             const uint8_t sda,
             const uint8_t scl)
    : i2cBase(dev_addr, sda, scl) {};
  void Init();
  uint16_t RawValue(const uint8_t channel);
 private:
   void pollUntilReady();
}
