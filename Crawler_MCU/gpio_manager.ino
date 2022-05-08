void setupGpio() {
  pinMode(LED_COMM, OUTPUT);
  
  pinMode(L_MOTOR_SPEED, OUTPUT);
  pinMode(L_MOTOR_FWD, OUTPUT);
  pinMode(L_MOTOR_BWD, OUTPUT);  
  pinMode(R_MOTOR_SPEED, OUTPUT);
  pinMode(R_MOTOR_FWD, OUTPUT);
  pinMode(R_MOTOR_BWD, OUTPUT);
  
  digitalWrite(LED_COMM, HIGH);
  digitalWrite(L_MOTOR_FWD, LOW);
  digitalWrite(L_MOTOR_BWD, LOW); 
  digitalWrite(R_MOTOR_FWD, LOW);
  digitalWrite(R_MOTOR_BWD, LOW);
     
  analogWriteRange(PWM_RANGE);
  analogWriteFreq(PWM_FREQUENCY);
  
  analogWrite(L_MOTOR_SPEED, 0);
  analogWrite(R_MOTOR_SPEED, 0);
}
