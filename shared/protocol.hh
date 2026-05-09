#ifndef PROTOCOL_HH
#define PROTOCOL_HH

#include <cstdint>
#include <stddef.h>

namespace Protocol {
  static constexpr uint16_t PORT = 42069;
  static constexpr uint16_t START_BYTES = 0xDEAD;
  static constexpr uint16_t SAMPLES_PER_PACKET = 256;
  static constexpr uint8_t POLYNOMIAL = 0x07;
  static constexpr uint8_t INIT_VAL = 0x00;
  uint8_t calculate_crc8(const unsigned char* data, uint16_t len,
                                    uint8_t poly, uint8_t init_val);
}

#pragma pack(push, 1)
struct AudioFrame {
  uint16_t start;
  uint8_t count;
  int32_t samples[Protocol::SAMPLES_PER_PACKET];
  uint8_t crc;
};
#pragma pack(pop)

#endif 
