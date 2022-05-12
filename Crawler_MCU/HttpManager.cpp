#include "HttpManager.h"

HttpManager::HttpManager(int ledPin) {
  this->ledPin = ledPin;
  lastMillisOfLedComm = millis();
  lastMillisOfIncomingRequest = millis();
  pinMode(ledPin, OUTPUT);  
  turnOffLed();   
}

void HttpManager::handleRequest(AsyncWebServerRequest *request, int (& targetSpeedValue) [2]) {
  turnOnLed();
  lastMillisOfLedComm = millis();  
  lastMillisOfIncomingRequest = millis();  
  String sLeft = "0";
  String sRight = "0";
  if (request->hasParam("left") && request->hasParam("right")) {
    sLeft = request->getParam("left")->value();
    sRight = request->getParam("right")->value();
  }  
  String response = "{\"left\":" + sLeft + ",\"right\":" + sRight + "}";
  Serial.print("response => ");
  Serial.println(response);
  request->send(200, "text/plain", response);
  targetSpeedValue[0] = sLeft.toInt();
  targetSpeedValue[1] = sRight.toInt();
}

void HttpManager::maintenance() {
  turnOffCommunicationLedAfterBlink();
}

boolean HttpManager::isConnectionNotAvailable() {
  if (millis() >= lastMillisOfIncomingRequest + REQUEST_TIMEOUT) {
    Serial.println("Connection not available, motors stopped.");
    lastMillisOfIncomingRequest = millis();
    return true;
  }
  return false;
}

void HttpManager::turnOffCommunicationLedAfterBlink() {
  if (!digitalRead(ledPin) && millis() >= lastMillisOfLedComm + COMM_LED_BLINK_DURATION) {
    turnOffLed();
  }
}

void HttpManager::turnOnLed() {
  digitalWrite(ledPin, LOW);
}

void HttpManager::turnOffLed() {
  digitalWrite(ledPin, HIGH);
}
