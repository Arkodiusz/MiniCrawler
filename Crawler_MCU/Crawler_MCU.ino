#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED_WIFI 2 // D4 (built in LED)
#define LED_COMM 16 // D0 (built in LED)

#define L_MOTOR_SPEED 5 // D1
#define L_MOTOR_FWD 4 // D2
#define L_MOTOR_BWD 0 // D3
#define R_MOTOR_SPEED 13 // D7
#define R_MOTOR_FWD 14 // D5
#define R_MOTOR_BWD 12 // D6

#define WIFI_MODE_SELECTOR 9 // SD2

#define PWM_FREQUENCY 1000
#define PWM_RANGE 100
#define PWM_DUTY_CYCLE_PER_LEVEL 10

ESP8266WebServer server(80);

unsigned long lastMillisOfLedComm;
unsigned long lastMillisOfIncomingRequest;
unsigned long lastMillisOfMotorsSpeedChange;

void setup() {
  Serial.begin(9600);
  Serial.println("\n\n===============================");
  
  setupGpio();
  if (digitalRead(WIFI_MODE_SELECTOR)) {
    setupAccessPoint();
  } else {
    connectToWiFi();
  }  
  setupServer();
  
  lastMillisOfIncomingRequest = millis(); 
  lastMillisOfMotorsSpeedChange = millis(); 
  
  delay(2000);
}

void loop() {
  server.handleClient();
  
  turnOffCommunicationLedAfterBlink();

  watchConnectionAvailability();

  setMotorsSpeed();
  
}
