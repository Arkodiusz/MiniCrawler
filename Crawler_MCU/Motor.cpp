#include "Motor.h"

Motor::Motor() {  
}

Motor::Motor(int pinSpeed, int pinFwd, int pinBwd) {
  this->pinSpeed = pinSpeed;
  this->pinFwd = pinFwd;
  this->pinBwd = pinBwd;  

  pinMode(pinSpeed, OUTPUT);
  pinMode(pinFwd, OUTPUT);
  pinMode(pinBwd, OUTPUT);  
    
  analogWrite(pinSpeed, 0);
  digitalWrite(pinFwd, LOW);
  digitalWrite(pinBwd, LOW);   
}

void Motor::setRotation(int targetSpeed) {

  if (actualSpeed > targetSpeed) {
    actualSpeed -= SPEED_CHANGE_STEP;     
  } else if (actualSpeed < targetSpeed) {
    actualSpeed += SPEED_CHANGE_STEP;
  }
  
  if (actualSpeed > 0) {
    digitalWrite(pinFwd, HIGH);
    digitalWrite(pinBwd, LOW);
  } else if (actualSpeed < 0) {
    digitalWrite(pinFwd, LOW);
    digitalWrite(pinBwd, HIGH);
  } else {
    digitalWrite(pinFwd, LOW);
    digitalWrite(pinBwd, LOW);
  }  
  analogWrite(pinSpeed, abs(actualSpeed));
}
