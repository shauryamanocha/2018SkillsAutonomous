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
  rearLeft.write((1-speed)*90);
 //  Serial.println(digitalRead(4));
Serial.print("4");
//  Serial.println(digitalRead(7)); rearRight.write((1+speed)*90);
    delay(angle * 2);
  }
  void turnRight(int angle, int speed) {
  rearLeft.write((1+speed)*90);
  rearRight.write(1-speed*90);
    delay(angle * 2);
  }

  void drive(int leftSpeed, int rightSpeed, int duration) {
  rearLeft.write((1+leftSpeed)*90);
  rearRight.write((1+rightSpeed)*90);
  delay(duration);
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

void setup() {
  rearLeftPin = 9;
  rearRightPin = 10;
  rearLeft.attach(9);
  rearRight.attach(10);
}

void loop() {
  //rearLeft.write(150);
  //rearRight.write(30);
  drive(1, 100);
  //turnRight(1, 1);

}
