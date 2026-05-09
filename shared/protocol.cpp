#include "protocol.hh" 

uint8_t Protocol::calculate_crc8(const unsigned char* data, uint16_t len,
                                    uint8_t poly, uint8_t init_val) {
  uint8_t res_crc = init_val;

  while (--len >= 0) {
    res_crc ^= *data++;
    for (uint8_t i = 0 ; i < 8; ++i)
      res_crc = res_crc & 0x80 ? (res_crc << 1) ^ poly : res_crc << 1;
  }
  return res_crc;
}
