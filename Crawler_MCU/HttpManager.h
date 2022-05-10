#ifndef HttpManager_h
#define HttpManager_h

#include <Arduino.h>
#include <ESP8266WebServer.h>

#include "PARAMS.h"

class HttpManager {
  
  private:
    int ledPin;
    unsigned long lastMillisOfLedComm;
    unsigned long lastMillisOfIncomingRequest; 
    void turnOffCommunicationLedAfterBlink();    
    
  public:
    ESP8266WebServer server = ESP8266WebServer(SERVER_PORT);
    HttpManager(int ledPin);
    void handleRequest(int (& targetSpeedValue) [2]);
    void handleClient();
    boolean isConnectionNotAvailable();
};
#endif
