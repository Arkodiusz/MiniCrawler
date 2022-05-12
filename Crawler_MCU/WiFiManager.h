#ifndef WiFiManager_h
#define WiFiManager_h

#include <ESP8266WiFi.h>
#include "PARAMS.h"
#include "WiFiCredentials.h"

class WiFiManager {
  
  private:
    int ledPin;
    int selectorPin;
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
