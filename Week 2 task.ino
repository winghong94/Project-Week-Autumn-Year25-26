#include <LiquidCrystal.h>

// --- MOTOR PINS ---
#define enA 11
#define in1 1
#define in2 2

#define enB 3
#define in3 12
#define in4 13

const int rightIrPin = A5;
const int leftIrPin = A4;
const int midIrPin = A3;

#define LEFT_THRES 550
#define RIGHT_THRES 500
#define MID_THRES 350

// --- DIRECTIONS ---
#define FORWARD 1
#define BACKWARD 0

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int last = 0;  // 0=Unknown, 1=Left, 2=Right
int turnSpeed = 180;
int straightSpeed = 120;
int stopCounter;
void rotateMotorA(int speed, int direction) {
  speed = constrain(speed, 0, 255);
  analogWrite(enA, speed);
  if (direction == FORWARD) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
}

void rotateMotorB(int speed, int direction) {
  speed = constrain(speed, 0, 255);
  analogWrite(enB, speed);
  if (direction == FORWARD) {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
}

void stopMotors() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(rightIrPin, INPUT);
  pinMode(leftIrPin, INPUT);
  pinMode(midIrPin, INPUT);

  stopMotors();
}

void loop() {
  int leftVal = analogRead(leftIrPin);
  int midVal = analogRead(midIrPin);
  int rightVal = analogRead(rightIrPin);

  lcd.clear();
  lcd.setCursor(0, 0);
  char LnM[15];
  sprintf(LnM, "R:%03d   M:%03d", leftVal, midVal);
  lcd.print(LnM);
  lcd.setCursor(0, 1);
  sprintf(LnM, "R:%03d", rightVal);
  lcd.print(LnM);

  if (leftVal > LEFT_THRES && rightVal > RIGHT_THRES && midVal < MID_THRES) {
    stopCounter++;
    lcd.setCursor(8, 1);
    lcd.print("count:");
    lcd.print(stopCounter);
    if (stopCounter > 20) {
      if (last == 1) {
        rotateMotorA(200, FORWARD);
        rotateMotorB(200, BACKWARD);
      } else if (last == 2) {
        rotateMotorA(200, BACKWARD);
        rotateMotorB(200, FORWARD);
      }
      stopCounter = 0;
    }
  } else {
    if (leftVal < LEFT_THRES) {
      last = 1;
      rotateMotorB(0, BACKWARD);
      rotateMotorA(turnSpeed, BACKWARD);
    } else if (rightVal < RIGHT_THRES) {
      last = 2;
      rotateMotorB(turnSpeed, BACKWARD);
      rotateMotorA(0, BACKWARD);
    } else if (midVal > MID_THRES) {
      rotateMotorA(straightSpeed, BACKWARD);
      rotateMotorB(straightSpeed, BACKWARD);
    } else {
      stopCounter = 0;
    }
  }
}
