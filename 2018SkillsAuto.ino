
// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define CW  0
#define CCW 1

// Motor definitions to make life easier:
#define MOTOR_A 0
#define MOTOR_B 1

// Pin Assignments //
// Don't change these! These pins are statically defined by shield layout
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 11; // PWM control (speed) for motor B
const byte DIRA = 12; // Direction control for motor A
const byte DIRB = 13; // Direction control for motor B
int leftSens = 0;
int rightSens = 0;
int centerSens = 0;
boolean onLine = false;
int prevDir = 5;
boolean centerSees = false;
int threshold = 300;
boolean done = false;

void setup()
{
  setupArdumoto(); // Set all pins as outputs
  Serial.begin(9600);
  delay(2000);
  drive(0);

}
//************//
void loop()
{
  if (!done) {
    updateLines();
    driveToLine();
    delay(1000);
    drive(10);
    delay(200);
    turnLeft();
    delay(3000);
    drive(-10);
    delay(450);
    followLine(150);
    delay(1000);
    drive(-10);
    delay(1000);
    turnRight();
    delay(5400);
    drive(10);
    delay(3000);
    driveToLine();
    followLine(600);
    done = true;

  } else {
    drive(0);
  }


}

// driveArdumoto drives 'motor' in 'dir' direction at 'spd' speed
void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }
}

void drive(int speed) {
  int newSpeed = map(speed, -10, 10, -255, 255);
  int leftDir = -1;
  int rightDir = -1;
  if (newSpeed > 0) {
    leftDir = 1;
    rightDir = 0;
  } else {
    rightDir = 1;
    leftDir = 0;
  }
  driveArdumoto(MOTOR_A, leftDir, abs(newSpeed));
  driveArdumoto(MOTOR_B, rightDir, abs(newSpeed));
}

void turnRight() {
  driveArdumoto(MOTOR_A, CW, 80);
  driveArdumoto(MOTOR_B, CW, 80);
  //delay(200);
}

void turnLeft() {
  driveArdumoto(MOTOR_A, CCW, 80);
  driveArdumoto(MOTOR_B, CCW, 80);
  //delay(200);
}

void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}

void updateLines() {
  leftSens = digitalRead(2);
  centerSens = digitalRead(5);
  rightSens = digitalRead(4);
  //Serial.println(centerSens);
  Serial.print(leftSens);
  Serial.print(centerSens);
  Serial.println(rightSens);
}

void driveToLine() {
  updateLines();
  drive(10);
  while (leftSens  == 0 && rightSens  == 0 &  centerSens  == 0) {
    onLine = false;
    updateLines();
    drive(10);
  }
  if (leftSens == 1 || centerSens == 1 || rightSens == 1) {
    drive(0);
    Serial.println("found line");
    onLine = true;
  } else {
    driveToLine();
  }
}

void followLine(int duration) {
  int elapsedTime = 0;
  while (elapsedTime < duration) {
    Serial.print(leftSens);
    Serial.print(centerSens);
    Serial.println(rightSens);
    updateLines();
    if (leftSens  == 1 && rightSens  == 0 && centerSens == 0)  {
      prevDir = -1;
      turnLeft();
      // centerSees = false;
    }
    if (leftSens  == 0 && rightSens  == 1 && centerSens == 0) {
      prevDir = 1;
      turnRight();
      // centerSees = false;
    }

    if (leftSens  == 0 && rightSens  == 0 && centerSens  == 0) {
      drive(6);
      //    // centerSees = false;
      //    if (prevDir  == 1) {
      //      turnRight();
      //
      //    } else if (prevDir == -1) {
      //      turnLeft();
      //    }
    }
    if (centerSens  == 1 && !centerSees) {
      centerSees = true;
      drive(10);
      Serial.println("pressed");
    }
    if (centerSees && centerSens  == 0) {
      prevDir *= -1;
      centerSees = false;
      Serial.println("released");
    }
    elapsedTime++;
  }
}

