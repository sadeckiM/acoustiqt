#include <Arduino.h>
#include "microphone.hh"
#include "wifi.hh"

Microphone *mic;
WiFi_UDP *wifi;

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(1000);
  wifi = new WiFi_UDP();
  wifi->init_wifi();
  mic = new Microphone(12, 13, 14);
  Serial.println("Wchodze do loop");
}

void loop() {
  if (!wifi->is_connected()) {
    delay(100);
    return;
  }

  int32_t samples = mic->read_raw_data_to_buffer();

  if (samples == 0) {
    Serial.println("0 próbek");
    delay(500);
    return;
  }

  if (samples > 0) {
    Serial.println("mam próbki w main");
    const int32_t* data = mic->get_buffer();
    wifi->send_audio_data(data);
    static uint16_t counter = 0;
    if (++counter % 100 == 0) {
      Serial.print(".");
    }
  }
} 
