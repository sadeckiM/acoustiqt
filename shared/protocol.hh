#ifndef PROTOCOL_HH
#define PROTOCOL_HH

#include <cstdint>

namespace Protocol {
  static constexpr uint16_t PORT = 42069;
  static constexpr uint16_t START_BYTES = 0xDEAD;
  static constexpr uint16_t SAMPLES_PER_PACKED = 256;
  static constexpr uint8_t POLYNOMIAL = 0x07;
  static constexpr uint8_t INIT_VAL = 0x00;
}

#pragma pack(push, 1)
struct AudioFrame {
  uint16_t start;
  uint8_t len;
  int32_t samples[Protocol::SAMPLES_PER_PACKED];
  uint8_t crc;
};
#pragma pack(pop)

#endif 
