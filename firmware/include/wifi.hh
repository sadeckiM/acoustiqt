#ifndef WIFI_HH
#define WIFI_HH

#include <Arduino.h>
#include <NetworkUdp.h>
#include <WiFi.h>

class WiFi_UDP {
  const char * NETWORK_NAME = "2.4G-Vectra-WiFi-94A317";
  const char * NETWORK_PASSWORD = "s8bng1zy0qli73vo";
  const char * UDP_ADDR = "192.168.0.255";
  const int PORT = 6565;
  bool connected = false;
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
