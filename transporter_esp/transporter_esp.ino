#include <ESP8266WiFi.h>
#include <Servo.h>
#include <ESP8266WebServer.h>
#include "WiFiCredentials.h"

const char* ssid = WIFI_SSID; // wifi credentials imported from WiFiCredentials.h (not staged to git) 
const char* password = WIFI_PASSWORD;

const uint8_t pinLedWiFi = 2;
const uint8_t pinLedComm = 16;
const uint8_t pinServoL = 5;
const uint8_t pinServoR = 4;

ESP8266WebServer server(80);

Servo servoL;
Servo servoR;

const uint16_t L_STOP = 1455;
const uint16_t R_STOP = 1435;
const uint16_t MS_PER_SPEED_LEVEL = 20;

unsigned long lastMillis;

void controlMovement() {
  digitalWrite(pinLedComm, LOW);
  lastMillis = millis();
  String left = server.arg("left");
  String right = server.arg("right");
  int8_t speedLevelL = left.toInt();
  int8_t speedLevelR = right.toInt();
  servoController(speedLevelL, speedLevelR);
  server.send(204, "");
}

void servoController(int8_t speedLevelL, int8_t speedLevelR) {
  int16_t speedL = speedLevelL * MS_PER_SPEED_LEVEL;
  int16_t speedR = speedLevelR * MS_PER_SPEED_LEVEL;

  Serial.print("\n LEFT: ");
  Serial.print(speedL);  
  Serial.print(" => ");
  Serial.print(L_STOP + speedL);
  Serial.print("\nRIGHT: ");  
  Serial.print(speedR); 
  Serial.print(" => ");  
  Serial.print(R_STOP - speedR);
  
  servoL.writeMicroseconds(L_STOP + speedL);
  servoR.writeMicroseconds(R_STOP - speedR);
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("\n\nConnecting to WiFi.");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(pinLedWiFi, !digitalRead(pinLedWiFi));
  }
  Serial.print("\nConnected to: ");
  Serial.print(WiFi.SSID());
  Serial.print("\nIP address: ");
  Serial.print(WiFi.localIP());
  digitalWrite(pinLedWiFi, LOW);
}

void setup() {
  Serial.begin(9600);
  Serial.print("\n\n===============================");

  pinMode(pinLedWiFi, OUTPUT);
  digitalWrite(pinLedWiFi, HIGH);
  pinMode(pinLedComm, OUTPUT);
  digitalWrite(pinLedComm, HIGH);

  servoL.attach(pinServoL);
  servoR.attach(pinServoR);
  servoController(0, 0);

  connectToWiFi();
  
  server.on("/move", controlMovement);
  server.begin();

  delay(2000);
}

void loop() {
  server.handleClient();
  if (millis() > lastMillis + 100) {
    digitalWrite(pinLedComm, HIGH);
  }
}
