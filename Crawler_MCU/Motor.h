#ifndef Motor_h
#define Motor_h

#include <Arduino.h>
#include "PARAMS.h"

class Motor {
  
  private:
    int pinSpeed;
    int pinFwd;
    int pinBwd;        
    int actualSpeed;
    
  public:
    Motor();
    Motor(int pinSpeed, int pinFwd, int pinBwd);
    void setRotation(int targetSpeed);
};
#endif
