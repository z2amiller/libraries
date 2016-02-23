class i2cBase {
 public:
  // With the single argument constructor, only set the address,
  // but do not start the Wire library.
  i2cBase(const uint8_t dev_addr)
    : i2c_addr_(dev_addr) {}
  // If passed the SDA and SCL pins, the constructor will
  // initialize the Wire library.
  i2cBase(const uint8_t dev_addr,
          const uint8_t sda,
          const uint8_t scl):

  virtual void Init() {};

 protected:
   uint8_t read8(const uint8_t addr);
   uint16_t read16(const uint8_t addr);
   void write8(const uint8_t addr, const uint8_t data);

 private:
  uint8_t i2c_addr_;
};
