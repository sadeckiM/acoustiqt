#ifndef MICROPHONE_HH
#define MICROPHONE_HH

#include <Arduino.h>

#define I2S_WS 25
#define I2S_SCK 33
#define I2S_SD 32

#define YELLOW_LED 26
#define RED_LED 27

#define I2S_SAMPLE_RATE 16000
#define I2S_BUFFER_SIZE 1024

bool init_microphone(int pin_sck, int pin_ws, int pin_sd);
int32_t use_microphone();
inline void togglePin(int pin) { digitalWrite(pin, !digitalRead(pin)); }

#endif
