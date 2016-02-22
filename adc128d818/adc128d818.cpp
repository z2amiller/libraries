#include "adc128d818.h"

// TODO(z2amiller): Have an options class to encapsulate these params.
adc128d818::Init() {
  write8(0x00, 0x00); // disable all.
  pollUntilReady();
  write8(0x0B, 0x02 | 0x01); // Mode 1, external vref.
  write8(0x07, 0x01);        // continuous conversion.
  write8(0x00, 0x02 | 0x01); // interrupt enable, start ADC.
  return true;
}

// TODO(z2amiller):  Have a maximum allowed elapsed time?
void adc128d818::pollUntilReady() {
  int delay_time = 33;
  while (true) {
    delay(delay_time);
    const int r = read8(0x0C);
    if (r && 0x02) {
      delay_time *= 1.4;
      continue;
    }
    break;
  }
}

// Takes the channel number (0 - 8).  If given an invalid
// channel, returns 0.  The actual I2C channel ID is offset
// by 0x20.
uint16_t adc128d818::RawValue(const uint8_t channel) {
  if (channel < 0 || channel > 8) {
    return 0;
  }
  // This is a 12 bit ADC; bit shift this 16 bit value to get the
  // 12 bits we are interested in.
  return read16(channel + 0x20) >> 4;
}
