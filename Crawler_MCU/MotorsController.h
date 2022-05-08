#ifndef MotorsController_h
#define MotorsController_h

#include "Motor.h"

class MotorsController {
    
  private:
    Motor motorLeft;
    Motor motorRight;    
    int targetSpeedL;
    int targetSpeedR;
    unsigned long lastMillisOfMotorsSpeedChange;    
    
  public:
    MotorsController();
    MotorsController(Motor motorLeft, Motor motorRight);
    void setTargetSpeed(int speedLevelL, int speedLevelR);
    void setRotation();
};
#endif
