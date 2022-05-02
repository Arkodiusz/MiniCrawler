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
  setMotorsRotation(speedLevelL, speedLevelR);
  String response = "{\"left\":" + left + ",\"right\":" + right + "}";
  Serial.print("response => ");
  Serial.println(response);
  server.send(200, "text/plain", response);
}
