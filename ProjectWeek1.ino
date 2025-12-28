#include <LiquidCrystal.h>

#define enA 11  // PWM pin for speed control
#define in1 13  // Input pin 1
#define in2 12  // Input pin 2

// Define the pins for Motor B
#define enB 3  // PWM pin for speed control
#define in3 2  // Input pin 3
#define in4 1  // Input pin 4


// Define constants for direction
#define FORWARD 1
#define BACKWARD 0

// initialize the library with the numbers of the interface pins
// LCD(RS, enable, d4, d5, d6, d7)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
unsigned long lastMillis;
unsigned long lastLCD;
// Analog pin for key detection
const int analogPin = A0;

// Function to rotate a motor
void rotateMotorA(int speed, int direction) {
  analogWrite(enA, speed);  // Set speed using PWM
  if (direction == FORWARD) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (direction == BACKWARD) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
}

// Function to rotate Motor B
void rotateMotorB(int speed, int direction) {
  analogWrite(enB, speed);  // Set speed using PWM
  if (direction == FORWARD) {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else if (direction == BACKWARD) {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
}

// Function to stop the motors
void stopMotors() {
  // Set speed to 0
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  // Set direction pins to LOW
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time");


  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initialize motors in a stopped state
  stopMotors();

  lastMillis = millis();
}

void loop() {
  lcd.setCursor(0, 1);
  unsigned long milliseconds = (millis() - lastMillis) % 1000;
  unsigned long seconds = (millis() - lastMillis) / 1000;
  char formattedTime[7];
  sprintf(formattedTime, "%02ld:%03ld", seconds, milliseconds);
  lcd.print(formattedTime);
  if (millis() - lastMillis < 10002) {
    rotateMotorA(255, FORWARD);
    rotateMotorB(208, FORWARD);
  } else {
    
    stopMotors();
    while (1)
      ;
  }
}
