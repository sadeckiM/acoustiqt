#include "wifi.hh"
#include "protocol.hh"

WiFi_UDP myWiFi;

void WiFi_UDP::connect_to_wifi(const char *ssid, const char *pwd) {
  Serial.println("Connecting to WiFi network: " + String(ssid));
  WiFi.disconnect(true);
  WiFi.onEvent(WiFi_UDP::wifi_event);
  WiFi.begin(ssid, pwd);
}

void WiFi_UDP::wifi_event(WiFiEvent_t event, WiFiEventInfo_t info) {
  switch (event) {
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      myWiFi.handle_connected();
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.print("WiFi lost connection. ");
      Serial.println(info.wifi_sta_disconnected.reason);
      myWiFi.handle_disconnected();
      break;
    default: break;
  }
}

void WiFi_UDP::handle_connected() {
  Serial.print("WiFi connected, IP: ");
  Serial.println(WiFi.localIP());

  connected = true;
  udp.begin(WiFi.localIP(), Protocol::PORT);

  if (Protocol::PORT < 1024 || Protocol::PORT > 65535) {
    Serial.println("handle_connected: bad port.");
    return;
  }
  // udp.beginPacket(UDP_ADDR, PORT);
  // udp.print("Czas: ");
  // udp.print(static_cast<ulong>(millis() / 1000));
  // udp.endPacket();
}

void WiFi_UDP::handle_disconnected() {
  Serial.println("WiFi lost connection.");
  connected = false;
  udp.stop();
}

void WiFi_UDP::send_audio_data(const int32_t *data, size_t count) {
  if (!connected) return;

  udp.beginPacket(UDP_ADDR, Protocol::PORT);
  udp.write(reinterpret_cast<const uint8_t*>(data), count * sizeof(int32_t));
  udp.endPacket();
}
