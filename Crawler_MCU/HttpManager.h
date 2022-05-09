#ifndef HttpManager_h
#define HttpManager_h

#include <Arduino.h>
#include <ESP8266WebServer.h>

#include "PARAMS.h"

class HttpManager {
  
  private:
    int ledPin;
    int left;
    int right;
    unsigned long lastMillisOfLedComm;
    unsigned long lastMillisOfIncomingRequest; 
    void turnOffCommunicationLedAfterBlink();    
    
  public:
    ESP8266WebServer server = ESP8266WebServer(SERVER_PORT);
    HttpManager(int ledPin);
    void handleRequest();
    boolean isConnectionNotAvailable();
    void handleClient();
    int getParameterLeft();
    int getParameterRight();
};
#endif
