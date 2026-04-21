#include <Arduino.h>
#include "microphone.hh"
#include "wifi.hh"

void togglePin(int pin) {
  digitalWrite(pin, !digitalRead(pin));
}

Microphone mic(32, 25, 33);

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(1000);
  myWiFi.init_wifi();
}

WiFiUDP udp;

void loop() {
  // int32_t samples = mic.read_raw_data_to_buffer();

  udp.beginPacket("192.168.0.24", 12345);
  udp.print("czesc");
  if(udp.endPacket()) {
    Serial.println("Pakiet wyslany");
  } else {
    Serial.println("Blad");
  }
  // if(samples > 0) {
  //   myWiFi.send_audio_data(mic.get_buffer(), samples);
  // }
  delay(100);
}
