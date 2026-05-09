#ifndef WIFI_HH
#define WIFI_HH

#include <Arduino.h>
#include <NetworkUdp.h>
#include <WiFi.h>
#include "secrets.hh"

class WiFi_UDP {
  bool connected = false;
  uint8_t packet_count = 0;
  const char * UDP_ADDR = "255.255.255.255";
  NetworkUDP udp;
  void connect_to_wifi(const char * ssid, const char *pwd);
public:
  inline void init_wifi() { connect_to_wifi(NETWORK_NAME, NETWORK_PASSWORD);
    WiFi.setSleep(false); };
  void handle_connected();
  void handle_disconnected();
  void send_audio_data(const int32_t *raw_samples);
  inline const bool is_connected() const {return connected;}
};

#endif
