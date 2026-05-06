#ifndef WIFI_HH
#define WIFI_HH

#include <Arduino.h>
#include <NetworkUdp.h>
#include <WiFi.h>
#include "secrets.hh"

class WiFi_UDP {
  bool connected = false;
  const char * UDP_ADDR = "192.168.0.255";
  NetworkUDP udp;
  void connect_to_wifi(const char * ssid, const char *pwd);
public:
  inline void init_wifi() { connect_to_wifi(NETWORK_NAME, NETWORK_PASSWORD);
    WiFi.setSleep(false); };
  static void wifi_event(WiFiEvent_t event, WiFiEventInfo_t info);
  void handle_connected();
  void handle_disconnected();
  void send_audio_data(const int32_t* data, size_t count);
};

extern WiFi_UDP myWiFi;

#endif
