static int leftSens, centerSens, rightSens;
int leftSensPin, centerSensPin, rightSensPin;
int lineThreshold;

void updateSensors() {
  leftSens = digitalRead(leftSensPin);
  rightSens = digitalRead(rightSensPin);
  centerSens = digitalRead(centerSensPin);
}

void followLine(int duration) {
  static int elapsedTime = 0;
  while (elapsedTime < duration) {
    updateSensors();
    if (leftSens < lineThreshold && rightSens < lineThreshold && centerSens > lineThreshold) {
      drive(1, 10);
    } else if (leftSens > lineThreshold && rightSens < lineThreshold) {
      drive(-1, 1, 10);
    } else if (leftSens < lineThreshold && rightSens > lineThreshold) {
      drive(1, -1, 10);
    } else {
      drive(1, 10);
    }
    elapsedTime++;
  }
}
