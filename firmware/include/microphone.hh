#ifndef MICROPHONE_HH
#define MICROPHONE_HH

#include <Arduino.h>
#include <driver/i2s.h>

#define BUFFER_SIZE 512
#define SAMPLE_RATE 16000

class Microphone {
  i2s_config_t i2s_config;
  i2s_pin_config_t i2s_mic_pins;
  int32_t buffer[BUFFER_SIZE];
  int32_t last_sample;
  inline void togglePin(int pin) { digitalWrite(pin, !digitalRead(pin)); }
  int32_t read_raw_data_to_buffer();
public:
  Microphone(int32_t pin_sck, int32_t pin_ws, int32_t pin_sd, i2s_channel_fmt_t
             channel);
  int32_t get_rms(uint8_t shift = 14);
  inline const int32_t* get_buffer() const { return buffer; }
  inline const size_t get_buffer_sample_count() const { return last_sample; }
};

#endif
