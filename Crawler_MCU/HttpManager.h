#ifndef HttpManager_h
#define HttpManager_h

#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "PARAMS.h"

class HttpManager {
  
  private:
    int ledPin;
    unsigned long lastMillisOfLedComm;
    unsigned long lastMillisOfIncomingRequest; 
    void turnOffCommunicationLedAfterBlink();
    void turnOffLed();
    void turnOnLed();  
    
  public:
    AsyncWebServer server = AsyncWebServer(SERVER_PORT);
    HttpManager(int ledPin);
    void handleRequest(AsyncWebServerRequest *request, int (& targetSpeedValue) [2]);
    void maintenance();
    boolean isConnectionNotAvailable();
};
#endif
