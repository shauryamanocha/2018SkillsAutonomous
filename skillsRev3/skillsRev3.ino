#include <Servo.h>

static int leftSens, centerSens, rightSens;
int leftSensPin, centerSensPin, rightSensPin;
int lineThreshold;
int rearLeftPin, rearRightPin;
Servo rearLeft, rearRight;

void updateSensors() {
  leftSens = digitalRead(leftSensPin);
  rightSens = digitalRead(rightSensPin);
  centerSens = digitalRead(centerSensPin);

}
void drive(int speed, int duration) {
  //rearLeft.write((1+speed)*90);
  //rearRight.write((1+speed)*90);
  rearLeft.write(180);
  rearRight.write(180);
  delay(duration);
}

void turnLeft(int angle, int speed) {
  rearLeft.write((1-speed)*65);
    delay(angle * 2);
  }
  void turnRight(int angle, int speed) {
  rearLeft.write((1+speed)*65);
  rearRight.write(1-speed*65);
    delay(angle * 2);
  }

  void drive(int leftSpeed, int rightSpeed, int duration) {
  rearLeft.write((1+leftSpeed)*65);
  rearRight.write((1+rightSpeed)*65);
  delay(duration);
}
void followLine(int duration) {
  static int elapsedTime = 0;
  while (elapsedTime < duration) {
    updateSensors();
    if (leftSens == 0 && rightSens == 0 && centerSens == 1) {
      drive(1, 10);//drive straight
    } else if (leftSens == 1 && rightSens == 0) {
      drive(1, -1, 10);//turn right
    } else if (leftSens == 0 && rightSens == 1) {
      drive(-1, 1, 10);//turn left
    } else {
      drive(1, 10);//drive forward
    }
    elapsedTime++;
  }
}

void setup() {
  rearLeftPin = 9;
  rearRightPin = 10;
  rearLeft.attach(9);
  rearRight.attach(10);
  leftSensPin = 7;
  rightSensPin = 2;
  centerSensPin = 4;
}

void loop() {
  drive(1, 100);
}
