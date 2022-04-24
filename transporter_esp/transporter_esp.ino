#include <ESP8266WiFi.h>
#include <Servo.h>
#include <ESP8266WebServer.h>

const char* ssid = "SIEC 6G";
const char* password = "kmwtw999";

const uint8_t pinLed = 16;
const uint8_t pinServoL = 5;
const uint8_t pinServoR = 4;

ESP8266WebServer server(80);

Servo servoL;
Servo servoR;

uint8_t BWD = 0;
uint8_t STOP = 90;
uint8_t FWD = 180;

void controlMovement() {
  String left = server.arg("left");
  String right = server.arg("right");
  
  int valueL = validateValueOf(left);
  int valueR = 180 - validateValueOf(right);

  Serial.print("\nvalueL: ");
  Serial.print(valueL);
  Serial.print("\nvalueR: ");
  Serial.print(valueR);

  servoL.write(valueL);
  servoR.write(valueR);
  server.send(204, "");
}

int validateValueOf(String rawValue) {
  switch (rawValue.toInt()) {
    case 1: 
      return FWD;
      break;
    case -1:
      return BWD;
      break;
    default:
      return STOP;
  }
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("\n\nConnecting to WiFi.");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(pinLed, !digitalRead(pinLed));
  }
  Serial.print("\nConnected to: ");
  Serial.print(WiFi.SSID());
  Serial.print("\nIP address: ");
  Serial.print(WiFi.localIP());
  digitalWrite(pinLed, LOW);
}

void setup() {
  Serial.begin(9600);

  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, HIGH);

  servoL.attach(pinServoL);
  servoL.write(STOP);
  servoR.attach(pinServoR);
  servoR.write(STOP);

  connectToWiFi();
  
  server.on("/move", controlMovement);
  server.begin();

  delay(2000);
}

void loop() {
  server.handleClient();
}
