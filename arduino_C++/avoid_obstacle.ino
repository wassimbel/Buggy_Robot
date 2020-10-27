#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <Servo.h>
#define right_track A4
#define left_track A5
#define trig A2
#define echo A3
#define right_obstacle A0
#define left_obstacle A1


// initialize the motors and the servo motor

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_64KHZ);
Servo myservo;


long duration;
int how_far;
int where_am_i;
// setup the speed of motors, servo motor, and input, output pins

void setup() {
  Serial.begin(9600);
  myservo.attach(10);
  pinMode(right_track, INPUT);
  pinMode(left_track, INPUT);
  pinMode(right_obstacle, INPUT);
  pinMode(left_obstacle, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  motor1.setSpeed(155);
  motor2.setSpeed(155);
  motor3.setSpeed(155);
  motor4.setSpeed(155);
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

// returns the distance between the robot and the obstacle

int distance1() {
  myservo.write(0);
  digitalWrite(trig, LOW);
  delay(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  how_far = duration * 0.034 / 2;
  Serial.println(how_far);
  return(how_far);
}

// make the robot move without hitting obstacles

void avoid_obstacle() {
  while (true) {
    where_am_i = distance1();
    if (where_am_i > 10 && (digitalRead(right_obstacle)) && (digitalRead(left_obstacle)))
    {
      forward();
      delay(500);
      where_am_i = distance1();
    }
    if (where_am_i > 10 && (!digitalRead(right_obstacle)) && (!digitalRead(left_obstacle)))
    {
      freeze();
      delay(1000);
      backward();
      delay(1000);
      pivot_right();
      delay(500);
      where_am_i = distance1();
    }
    
    if (where_am_i > 10 && (!digitalRead(right_obstacle)) && (digitalRead(left_obstacle)))
    {
      turn_left();
      delay(1000);
      where_am_i = distance1();
    }
    if (where_am_i > 10 && (digitalRead(right_obstacle)) && (!digitalRead(left_obstacle)))
    {
      turn_right();
      delay(1000);
      where_am_i = distance1();
    }
    if (where_am_i <= 10 && (digitalRead(right_obstacle)) && (digitalRead(left_obstacle)))
    {
      freeze();
      delay(1000);
      backward();
      delay(500);
      where_am_i = distance1();
      pivot_left();
      delay(500);
    }
    if (where_am_i <= 10 && (digitalRead(right_obstacle)) && (digitalRead(left_obstacle)))
    {
      freeze();
      delay(1000);
      backward();
      delay(500);
      pivot_right();
      delay(500);
      where_am_i = distance1();
    }
  }
}
void test() {
  if (digitalRead(right_obstacle))
    Serial.println("obstacle");
  else
    Serial.println("no obstacle");
}

// running this loop repeatedly

void loop() {
  avoid_obstacle();
}
