#include <SoftwareSerial.h>
#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_64KHZ);

void setup() {
  Serial.begin(9600);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  motor1.setSpeed(100);
  motor2.setSpeed(100);
  motor3.setSpeed(100);
  motor4.setSpeed(100);
}


void pivot_right() {
  motor1.run(FORWARD);
  motor1.run(BACKWARD);
  motor1.run(BACKWARD);
  motor1.run(FORWARD);
}

void pivot_left() {
  motor1.run(BACKWARD);
  motor1.run(FORWARD);
  motor1.run(FORWARD);
  motor1.run(BACKWARD);
}

void forward() {
  motor1.run(FORWARD);              
  motor2.run(FORWARD);
  motor3.run(FORWARD);       
  motor4.run(FORWARD);
}

void backward() {
  motor1.run(BACKWARD);              
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);       
  motor4.run(BACKWARD);
}

void turn_right() {
  motor1.run(RELEASE);              
  motor2.run(FORWARD);
  motor3.run(FORWARD);       
  motor4.run(RELEASE);
}

void turn_left() {
  motor1.run(FORWARD);              
  motor2.run(RELEASE);
  motor3.run(RELEASE);       
  motor4.run(FORWARD);
}

void freeze() {
  motor1.run(RELEASE);              
  motor2.run(RELEASE);
  motor3.run(RELEASE);       
  motor4.run(RELEASE);
}

void follow_line() {
  if ((!digitalRead(A4)) && (!digitalRead(A5)))                                                                               forward();
  if ((digitalRead(A4)) && (!digitalRead(A5)))
      turn_left();
  if ((!digitalRead(A4)) && digitalRead(A5))
      turn_right();
}

void loop() {
  follow_line();
}
