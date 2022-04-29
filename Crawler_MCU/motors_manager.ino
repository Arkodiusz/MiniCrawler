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

  Serial.print("LEFT: ");
  Serial.println(speedL);  
  Serial.print("RIGHT: ");  
  Serial.println(speedR); 

  analogWrite(L_MOTOR_SPEED, speedL);
  analogWrite(R_MOTOR_SPEED, speedR);
}
