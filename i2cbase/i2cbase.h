class i2cBase {
 public:
  i2cBase(const uint8_t dev_addr,
          const uint8_t sda,
          const uint8_t scl):
  void Init();

 protected:
   uint8_t read8(const uint8_t addr);
   uint16_t read16(const uint8_t addr);
   void write8(const uint8_t addr, const uint8_t data);

 private:
  uint8_t i2c_addr_;
  uint8_t sda_pin_;
  uint8_t scl_pin_;
};
