#include <Servo.h>
//#include <Servos>
//#include<LineSensors>

void setup() {
  leftDrive.attach(leftDrivePin);
  rightDrive.attach(rightDrivePin);
}

void loop() {
  //rearLeft.write(150);
  //rearRight.write(30);
  drive(1, 100);
  //turnRight(1, 1);

}
