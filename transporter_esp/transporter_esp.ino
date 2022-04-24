#include <ESP8266WiFi.h>
#include <Servo.h>
#include <ESP8266WebServer.h>

const char* ssid = "SIEC 6G";
const char* password = "kmwtw999";

const uint8_t PinServoL = 5;
const uint8_t PinServoR = 4;

ESP8266WebServer server(80);

Servo servoL;
Servo servoR;

uint8_t FWD = 180;
uint8_t STOP = 90;
uint8_t BWD = 0;

void setup(){  
  Serial.begin(9600);

  servoL.attach(PinServoL);
  servoL.write(STOP);  
  servoR.attach(PinServoR);
  servoR.write(STOP);

  establishConnection();
  
  server.on("/stop", stopMovement);  
  server.on("/fwd", goForward);
  server.on("/bwd", goBackward);
  
  server.begin();
  
  delay(2000);
}

void loop() {
  server.handleClient();
}

void stopMovement() {
  servoL.write(STOP);
  servoR.write(STOP);
  server.send(204, "");
}

void goForward() {
  servoL.write(FWD);
  servoR.write(FWD);
  server.send(204, "");
}

void goBackward() {
  servoL.write(BWD);
  servoR.write(BWD);
  server.send(204, "");
}


void establishConnection() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.print("\nConnected to the WiFi network: ");
  Serial.print(WiFi.SSID());
  Serial.print(" IP address: ");
  Serial.print(WiFi.localIP());
}
