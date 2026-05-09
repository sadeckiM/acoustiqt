#include <Arduino.h>
#include "microphone.hh"
#include "wifi.hh"

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(1000);
  Microphone mic(32, 25, 33);
  WiFi_UDP myWiFi;
  myWiFi.init_wifi();

  while (1) {
    int32_t samples = mic.read_raw_data_to_buffer();

    if (samples > 0) {
      const int32_t* audio_data = mic.get_buffer();
      myWiFi.send_audio_data(audio_data);
    }
  }
}

void loop() {}
