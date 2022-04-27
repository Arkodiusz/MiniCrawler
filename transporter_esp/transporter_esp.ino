#include <ESP8266WiFi.h>
#include <Servo.h>
#include <ESP8266WebServer.h>
#include "WiFiCredentials.h"

const uint8_t LED_WIFI = 2;
const uint8_t LED_COMM = 16;

const uint8_t L_MOTOR_SPEED = 5;
const uint8_t L_MOTOR_FWD = 4;
const uint8_t L_MOTOR_BWD = 0;

const uint8_t R_MOTOR_SPEED = 13;
const uint8_t R_MOTOR_FWD = 14;
const uint8_t R_MOTOR_BWD = 12;

const uint8_t PWM_FREQUENCY = 1000;
const uint8_t PWM_RANGE = 100;
const uint8_t PWM_DUTY_CYCLE_PER_LEVEL = 10;

ESP8266WebServer server(80);

unsigned long lastMillis;

void handleMovementHttpRequest() {
  digitalWrite(LED_COMM, LOW);
  lastMillis = millis();
  String left = server.arg("left");
  String right = server.arg("right");
  int8_t speedLevelL = left.toInt();
  int8_t speedLevelR = right.toInt();
  setMotorsRotation(speedLevelL, speedLevelR);
  server.send(204, "");
}

void setMotorsRotation(int8_t speedLevelL, int8_t speedLevelR) {  
  if (speedLevelL > 0) {
    digitalWrite(L_MOTOR_FWD, HIGH);
    digitalWrite(L_MOTOR_BWD, LOW);
  } else if (speedLevelL < 0) {
    digitalWrite(L_MOTOR_FWD, LOW);
    digitalWrite(L_MOTOR_BWD, HIGH);
  } else {
    digitalWrite(L_MOTOR_FWD, LOW);
    digitalWrite(L_MOTOR_BWD, LOW);
  }

  if (speedLevelR > 0) {
    digitalWrite(R_MOTOR_FWD, HIGH);
    digitalWrite(R_MOTOR_BWD, LOW);
  } else if (speedLevelR < 0) {
    digitalWrite(R_MOTOR_FWD, LOW);
    digitalWrite(R_MOTOR_BWD, HIGH);
  } else {
    digitalWrite(R_MOTOR_FWD, LOW);
    digitalWrite(R_MOTOR_BWD, LOW);
  }

  int16_t speedL = abs(speedLevelL * PWM_DUTY_CYCLE_PER_LEVEL);
  int16_t speedR = abs(speedLevelR * PWM_DUTY_CYCLE_PER_LEVEL);

  Serial.print("\n LEFT: ");
  Serial.print(speedL);  
  Serial.print("\nRIGHT: ");  
  Serial.print(speedR); 

  analogWrite(L_MOTOR_SPEED, speedL);
  analogWrite(R_MOTOR_SPEED, speedR);
}

void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // wifi credentials imported from WiFiCredentials.h (not staged to git) 
  Serial.print("\n\nConnecting to WiFi.");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(LED_WIFI, !digitalRead(LED_WIFI));
  }
  Serial.print("\nConnected to: ");
  Serial.print(WiFi.SSID());
  Serial.print("\nIP address: ");
  Serial.print(WiFi.localIP());
  digitalWrite(LED_WIFI, LOW);
}

void setup() {
  Serial.begin(9600);
  Serial.print("\n\n===============================");

  pinMode(LED_WIFI, OUTPUT);
  digitalWrite(LED_WIFI, HIGH);
  
  pinMode(LED_COMM, OUTPUT);
  digitalWrite(LED_COMM, HIGH);

  pinMode(L_MOTOR_SPEED, OUTPUT);
  pinMode(L_MOTOR_FWD, OUTPUT);
  pinMode(L_MOTOR_BWD, OUTPUT);  
  pinMode(R_MOTOR_SPEED, OUTPUT);
  pinMode(R_MOTOR_FWD, OUTPUT);
  pinMode(R_MOTOR_BWD, OUTPUT);

  digitalWrite(L_MOTOR_FWD, LOW);
  digitalWrite(L_MOTOR_BWD, LOW); 
  digitalWrite(R_MOTOR_FWD, LOW);
  digitalWrite(R_MOTOR_BWD, LOW);
     
  analogWriteRange(PWM_RANGE);
  analogWriteFreq(PWM_FREQUENCY);
  
  analogWrite(L_MOTOR_SPEED, 0);
  analogWrite(R_MOTOR_SPEED, 0);

  connectToWiFi();
  
  server.on("/move", handleMovementHttpRequest);
  server.begin();

  delay(2000);
}

void loop() {
  server.handleClient();
  if (!digitalRead(LED_COMM) && (millis() > lastMillis + 100)) {
    digitalWrite(LED_COMM, HIGH);
  }
}
