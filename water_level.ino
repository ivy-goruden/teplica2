void water_level() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  levelSensor = microsecondsToCentimeters(duration);
  if (levelSensor != 0) {
    levelSensor = round((oldLevelSensor * (averageFactor - 1) + levelSensor) / averageFactor);
    oldLevelSensor = levelSensor;
  } else {
    levelSensor = oldLevelSensor;
  }
  Serial.print(levelSensor);
  Serial.print("cm");
  Serial.println();
  Serial.println();
}

int microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}