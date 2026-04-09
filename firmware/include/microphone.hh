#ifndef MICROPHONE_HH
#define MICROPHONE_HH

#include <Arduino.h>
#include <driver/i2s.h>

#define BUFFER_SIZE 512
#define SAMPLE_RATE 16000

class Microphone {
  i2s_config_t i2s_config;
  i2s_pin_config_t i2s_mic_pins;
  inline void togglePin(int pin) { digitalWrite(pin, !digitalRead(pin)); }
public:
  Microphone(int pin_sck, int pin_ws, int pin_sd, i2s_channel_fmt_t channel,
             ulong baud_rate);
  int32_t get_amplitude(uint8_t shift = 14);
};

#endif
