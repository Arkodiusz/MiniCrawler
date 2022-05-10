#include "WiFiManager.h"
#include "HttpManager.h"
#include "Motor.h"
#include "MotorsController.h"

WiFiManager wifi(WIFI_LED, WIFI_MODE_SELECTOR);
HttpManager httpManager(COMM_LED);
Motor motorLeft(L_MOTOR_SPEED, L_MOTOR_FWD, L_MOTOR_BWD);
Motor motorRight(R_MOTOR_SPEED, R_MOTOR_FWD, R_MOTOR_BWD);
MotorsController motors(motorLeft, motorRight);

void setup() {
  Serial.begin(115200);
  Serial.println();
  wifi.initialize();
  httpManager.server.on("/move", handleMovementHttpRequest);
  httpManager.server.begin();
  delay(2000);
}

void loop() {
  httpManager.handleClient();
  if (httpManager.isConnectionNotAvailable()) {
    motors.setTargetSpeed(0, 0);
  }
  motors.setRotation();  
}

void handleMovementHttpRequest() {  
  int targetSpeedValue[2];
  httpManager.handleRequest(targetSpeedValue);  
  motors.setTargetSpeed(targetSpeedValue[0], targetSpeedValue[1]);
}
