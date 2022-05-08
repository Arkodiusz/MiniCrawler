#include <ESP8266WebServer.h>

#include "WiFiManager.h"
#include "Motor.h"
#include "MotorsController.h"

#define WIFI_LED 2 // D4 (built in LED)
#define WIFI_MODE_SELECTOR 9 // SD2

#define L_MOTOR_SPEED 5 // D1
#define L_MOTOR_FWD 4 // D2
#define L_MOTOR_BWD 0 // D3
#define R_MOTOR_SPEED 13 // D7
#define R_MOTOR_FWD 14 // D5
#define R_MOTOR_BWD 12 // D6

#define LED_COMM 16 // D0 (built in LED)

ESP8266WebServer server(80);

WiFiManager wifi(WIFI_LED, WIFI_MODE_SELECTOR);

Motor motorLeft(L_MOTOR_SPEED, L_MOTOR_FWD, L_MOTOR_BWD);
Motor motorRight(R_MOTOR_SPEED, R_MOTOR_FWD, R_MOTOR_BWD);
MotorsController motors(motorLeft, motorRight);

unsigned long lastMillisOfLedComm;
unsigned long lastMillisOfIncomingRequest;

void setup() {
  Serial.begin(9600);
  Serial.println("\n\n===============================");
  
  pinMode(LED_COMM, OUTPUT);
  
  digitalWrite(LED_COMM, HIGH);   
       
  wifi.initialize();
  
  server.on("/move", handleMovementHttpRequest);  
  server.begin();
  
  lastMillisOfIncomingRequest = millis(); 
  
  delay(2000);
}

void loop() {
  server.handleClient();
  
  turnOffCommunicationLedAfterBlink();

  watchConnectionAvailability();

  motors.setRotation();  
}

void handleMovementHttpRequest() {
  digitalWrite(LED_COMM, LOW);
  lastMillisOfLedComm = millis();
  String left = server.arg("left");
  String right = server.arg("right");
  int8_t speedLevelL = left.toInt();
  int8_t speedLevelR = right.toInt();
  motors.setTargetSpeed(speedLevelL, speedLevelR);
  String response = "{\"left\":" + left + ",\"right\":" + right + "}";
  Serial.print("response => ");
  Serial.println(response);
  server.send(200, "text/plain", response);
  lastMillisOfIncomingRequest = millis();
}

void turnOffCommunicationLedAfterBlink() {
  int blinkDuration = 100;
  if (!digitalRead(LED_COMM) && (millis() > lastMillisOfLedComm + blinkDuration)) {
    digitalWrite(LED_COMM, HIGH);
  }
}

void watchConnectionAvailability() {
  if (millis() > lastMillisOfIncomingRequest + 3000) {
    motors.setTargetSpeed(0, 0);
    Serial.println("Connection not available, motors stopped.");
    lastMillisOfIncomingRequest = millis();
  }
}
