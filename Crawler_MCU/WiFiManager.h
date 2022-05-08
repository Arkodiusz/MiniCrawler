#ifndef WiFiManager_h
#define WiFiManager_h

#include <ESP8266WiFi.h>
#include "WiFiCredentials.h"

class WiFiManager {
  
  private:
    int ledPin;
    int selectorPin;
    
    IPAddress apIp = IPAddress(44,44,44,1);
    IPAddress apGateway = IPAddress(44,44,44,1);
    IPAddress apSubnet = IPAddress(255,255,255,0);
    
    String apSsid = "ESP_crawler_01";
    String apPassword = "";
    String staSsid = WIFI_STATION_SSID;
    String staPassword = WIFI_STATION_PASSWORD;

    void setupAccessPoint();
    void connectToWiFi();
    void turnOffLed();
    void turnOnLed();
    void toggleLed();
    
  public:
    WiFiManager(int ledPin, int selectorPin);
    void initialize();
};
#endif