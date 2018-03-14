 int leftDrivePin = 9;
 int rightDrivePin = 10;
 public Servo leftDrive;
 Servo rightDrive;

void drive(int speed, int duration); {
  leftDrive.write(180);
  rightDrive.write(180);
  delay(duration);
}

void turnLeft(int angle, int speed); {
  leftDrive.write((1 - speed) * 90);
  //  Serial.println(digitalRead(4));
  Serial.print("4");
  //  Serial.println(digitalRead(7)); rearRight.write((1+speed)*90);
  delay(angle * 2);
}
void turnRight(int angle, int speed); {
  leftDrive.write((1 + speed) * 90);
  rightDrive.write(1 - speed * 90);
  delay(angle * 2);
}

void drive(int leftSpeed, int rightSpeed, int duration); {
  leftDrive.write((1 + leftSpeed) * 90);
  rightDrive.write((1 + rightSpeed) * 90);
  delay(duration);
}
