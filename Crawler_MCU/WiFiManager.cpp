#include "WiFiManager.h"

WiFiManager::WiFiManager(int ledPin, int selectorPin) {
  this->ledPin = ledPin;
  this->selectorPin = selectorPin;
}

void WiFiManager::initialize() {
  pinMode(ledPin, OUTPUT);
  turnOffLed();

  pinMode(selectorPin, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.print("\nWiFi mode selected via SD2 pin: ");

  if (digitalRead(selectorPin)) {
    setupAccessPoint();
  } else {
    connectToWiFi();
  }
  turnOnLed();
}

void WiFiManager::setupAccessPoint() {
  Serial.println("ACCESS POINT");
  Serial.print("Setting soft-AP configuration... ");
  Serial.println(WiFi.softAPConfig(apIp, apGateway, apSubnet) ? "Ready" : "Failed!");

  Serial.print("Setting soft-AP SSID... ");
  Serial.println(WiFi.softAP(apSsid, apPassword) ? "Ready" : "Failed!");

  Serial.print("SSID: ");
  Serial.println(apSsid);
  Serial.print("PASS: ");
  Serial.println(apPassword);
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());
}

void WiFiManager::connectToWiFi() {
  Serial.println("STATION");
  Serial.print("Connecting.");
  WiFi.begin(staSsid, staPassword); // wifi credentials imported from WiFiCredentials.h (not staged to git)
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    toggleLed();
  }
  Serial.println();
  Serial.print("Connected to: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void WiFiManager::turnOffLed() {
  digitalWrite(ledPin, HIGH);
}

void WiFiManager::turnOnLed() {
  digitalWrite(ledPin, LOW);
}

void WiFiManager::toggleLed() {
  digitalWrite(ledPin, !digitalRead(ledPin));
}