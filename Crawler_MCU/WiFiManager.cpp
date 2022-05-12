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
  IPAddress apIp(SOFT_AP_IP);
  IPAddress apGateway(SOFT_AP_GATEWAY);
  IPAddress apSubnet(SOFT_AP_SUBNET);
  Serial.println(WiFi.softAPConfig(apIp, apGateway, apSubnet) ? "Ready" : "Failed!");

  Serial.print("Setting soft-AP SSID... ");
  Serial.println(WiFi.softAP(SOFT_AP_SSID, SOFT_AP_PASSWORD) ? "Ready" : "Failed!");

  Serial.print("SSID: ");
  Serial.println(SOFT_AP_SSID);
  Serial.print("PASS: ");
  Serial.println(SOFT_AP_PASSWORD);
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());
}

void WiFiManager::connectToWiFi() {
  Serial.println("STATION");
  Serial.print("Connecting.");
  WiFi.begin(WIFI_STATION_SSID, WIFI_STATION_PASSWORD); // wifi credentials imported from WiFiCredentials.h (not staged to git)
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
