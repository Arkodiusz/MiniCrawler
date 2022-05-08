#include "MotorsController.h"

MotorsController::MotorsController() {
}

MotorsController::MotorsController(Motor motorLeft, Motor motorRight) {
  this->motorLeft = motorLeft;
  this->motorRight = motorRight;
  analogWriteRange(PWM_RANGE);
  analogWriteFreq(PWM_FREQUENCY); 
  lastMillisOfMotorsSpeedChange = millis();  
  Serial.begin(9600);
}

void MotorsController::setTargetSpeed(int speedLevelL, int speedLevelR) {
  targetSpeedL = speedLevelL * PWM_DUTY_CYCLE_PER_LEVEL;
  targetSpeedR = speedLevelR * PWM_DUTY_CYCLE_PER_LEVEL;  
  Serial.print("TARGET LEFT: ");
  Serial.println(targetSpeedL);  
  Serial.print("TARGET RIGHT: ");  
  Serial.println(targetSpeedR); 
}

void MotorsController::setRotation() {
  if (millis() > lastMillisOfMotorsSpeedChange + 1000 / SPEED_CHANGE_FREQUENCY) {
    motorLeft.setRotation(targetSpeedL);
    motorRight.setRotation(targetSpeedR);
    lastMillisOfMotorsSpeedChange = millis();    
  }  
}
