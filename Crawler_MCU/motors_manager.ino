int16_t targetSpeedL = 0;
int16_t targetSpeedR = 0;

int16_t actualSpeedL = 0;
int16_t actualSpeedR = 0;

int16_t speedChangeStep = 1;


void setMotorsDirectionAndTargetSpeed(int8_t speedLevelL, int8_t speedLevelR) {   

  targetSpeedL = speedLevelL * PWM_DUTY_CYCLE_PER_LEVEL;
  targetSpeedR = speedLevelR * PWM_DUTY_CYCLE_PER_LEVEL;

  Serial.print("TARGET LEFT: ");
  Serial.println(targetSpeedL);  
  Serial.print("TARGET RIGHT: ");  
  Serial.println(targetSpeedR); 
}

void setMotorsSpeed() {
  int changeFrequency = 200; // 1-1000 Hz
  if (millis() > lastMillisOfMotorsSpeedChange + 1000 / changeFrequency) {
    
    if (actualSpeedL > targetSpeedL) {
      actualSpeedL -= speedChangeStep;     
    } else if (actualSpeedL < targetSpeedL) {
      actualSpeedL += speedChangeStep;
    }

//    if (targetSpeedL == 0) {
//      actualSpeedL = 0;
//    }

    if (actualSpeedR > targetSpeedR) {
      actualSpeedR -= speedChangeStep;     
    } else if (actualSpeedR < targetSpeedR) {
      actualSpeedR += speedChangeStep;
    }

//    if (targetSpeedR == 0) {
//      actualSpeedR = 0;
//    }


  //TODO: digital write only on change
    if (actualSpeedL > 0) {
    digitalWrite(L_MOTOR_FWD, HIGH);
    digitalWrite(L_MOTOR_BWD, LOW);
  } else if (actualSpeedL < 0) {
    digitalWrite(L_MOTOR_FWD, LOW);
    digitalWrite(L_MOTOR_BWD, HIGH);
  } else {
    digitalWrite(L_MOTOR_FWD, LOW);
    digitalWrite(L_MOTOR_BWD, LOW);
  }

  if (actualSpeedR > 0) {
    digitalWrite(R_MOTOR_FWD, HIGH);
    digitalWrite(R_MOTOR_BWD, LOW);
  } else if (actualSpeedR < 0) {
    digitalWrite(R_MOTOR_FWD, LOW);
    digitalWrite(R_MOTOR_BWD, HIGH);
  } else {
    digitalWrite(R_MOTOR_FWD, LOW);
    digitalWrite(R_MOTOR_BWD, LOW);
  }
  
  
  
    
//    Serial.print("ACTUAL  LEFT: ");  
//    Serial.println(actualSpeedL);
//    
//    Serial.print("ACTUAL RIGHT: ");  
//    Serial.println(actualSpeedR);
    
    analogWrite(L_MOTOR_SPEED, abs(actualSpeedL));
    analogWrite(R_MOTOR_SPEED, abs(actualSpeedR));

    lastMillisOfMotorsSpeedChange = millis();
    
  }
  
}
