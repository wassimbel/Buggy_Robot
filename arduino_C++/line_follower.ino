#include <SoftwareSerial.h>
#include <AFMotor.h>
#define right_track A4
#define left_track A5

// initialize the motors

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_64KHZ);

// setup the speed of motors and input, output pins
 
void setup() {
  Serial.begin(9600);
  pinMode(right_track, INPUT);
  pinMode(left_track, INPUT);
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);
}

// pivot the robot right

void pivot_right() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

// pivot the robot left

void pivot_left() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

// moving the robot forward 

void forward() {
  motor1.run(FORWARD);              
  motor2.run(FORWARD);
  motor3.run(FORWARD);       
  motor4.run(FORWARD);
}

// moving the robot backward

void backward() {
  motor1.run(BACKWARD);              
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);       
  motor4.run(BACKWARD);
}

// turning the robot left

void turn_left() {
  motor1.run(RELEASE);              
  motor2.run(FORWARD);
  motor3.run(FORWARD);       
  motor4.run(RELEASE);
}

// turning the robot right

void turn_right() {
  motor1.run(FORWARD);              
  motor2.run(RELEASE);
  motor3.run(RELEASE);       
  motor4.run(FORWARD);
}

// stopping the robot

void freeze() {
  motor1.run(RELEASE);              
  motor2.run(RELEASE);
  motor3.run(RELEASE);       
  motor4.run(RELEASE);
}

// make the robot follow a line(in this case black line)

void follow_line() {
  if ((!digitalRead(right_track)) && (!digitalRead(left_track)))
      forward();
  if ((digitalRead(right_track)) && (!digitalRead(left_track)))
      turn_left();
  if ((!digitalRead(right_track)) && digitalRead(left_track))
      turn_right();
}

// running this loop repeatedly

void loop() {
  follow_line();
}
