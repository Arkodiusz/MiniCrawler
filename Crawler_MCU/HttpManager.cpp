#include "HttpManager.h"

HttpManager::HttpManager(int ledPin) {
  this->ledPin = ledPin;
  lastMillisOfLedComm = millis();
  lastMillisOfIncomingRequest = millis();
  pinMode(ledPin, OUTPUT);  
  digitalWrite(ledPin, HIGH);   
}

void HttpManager::handleRequest() {
  digitalWrite(ledPin, LOW);
  lastMillisOfLedComm = millis();  
  lastMillisOfIncomingRequest = millis();
  String sLeft = server.arg("left");
  String sRight = server.arg("right");
  left = sLeft.toInt();
  right = sRight.toInt();
  String response = "{\"left\":" + sLeft + ",\"right\":" + sRight + "}";
  Serial.print("response => ");
  Serial.println(response);
  server.send(200, "text/plain", response);
}

void HttpManager::handleClient() {
  server.handleClient();  
  turnOffCommunicationLedAfterBlink();
}

boolean HttpManager::isConnectionNotAvailable() {
  if (millis() > lastMillisOfIncomingRequest + REQUEST_TIMEOUT) {
    Serial.println("Connection not available, motors stopped.");
    lastMillisOfIncomingRequest = millis();
    return true;
  }
  return false;
}

int HttpManager::getParameterLeft() {
  return left;
}

int HttpManager::getParameterRight() {
  return right;
}

void HttpManager::turnOffCommunicationLedAfterBlink() {
  if (!digitalRead(ledPin) && (millis() > lastMillisOfLedComm + COMM_LED_BLINK_DURATION)) {
    digitalWrite(ledPin, HIGH);
  }
}
