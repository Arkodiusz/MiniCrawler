void setupServer() { 
  server.on("/move", handleMovementHttpRequest);  
  server.begin();
}

void handleMovementHttpRequest() {
  digitalWrite(LED_COMM, LOW);
  lastMillisOfLedComm = millis();
  String left = server.arg("left");
  String right = server.arg("right");
  int8_t speedLevelL = left.toInt();
  int8_t speedLevelR = right.toInt();
  setMotorsDirectionAndTargetSpeed(speedLevelL, speedLevelR);
  String response = "{\"left\":" + left + ",\"right\":" + right + "}";
  Serial.print("response => ");
  Serial.println(response);
  server.send(200, "text/plain", response);
  lastMillisOfIncomingRequest = millis();
}

void turnOffCommunicationLedAfterBlink() {
  int blinkDuration = 100;
  if (!digitalRead(LED_COMM) && (millis() > lastMillisOfLedComm + blinkDuration)) {
    digitalWrite(LED_COMM, HIGH);
  }
}

void watchConnectionAvailability() {
  if (millis() > lastMillisOfIncomingRequest + 3000) {
    setMotorsDirectionAndTargetSpeed(0, 0);
    Serial.println("Connection not available, motors stopped.");
    lastMillisOfIncomingRequest = millis();
  }
}
