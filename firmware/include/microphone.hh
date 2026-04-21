#ifndef MICROPHONE_HH
#define MICROPHONE_HH

#include <Arduino.h>
#include "driver/i2s_std.h"

#define BUFFER_SIZE 100
#define SAMPLE_RATE 16000

class Microphone {
  i2s_chan_handle_t rx_handle;
  int32_t buffer[BUFFER_SIZE];
  int32_t last_sample;
  inline void togglePin(int pin) { digitalWrite(pin, !digitalRead(pin)); }
public:
  Microphone(int32_t pin_sck, int32_t pin_ws, int32_t pin_sd);
  int32_t get_rms(uint8_t shift = 14);
  inline const int32_t* get_buffer() const { return buffer; }
  inline const size_t get_buffer_sample_count() const { return last_sample; }
  int32_t read_raw_data_to_buffer();
};

#endif
