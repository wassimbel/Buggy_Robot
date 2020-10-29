#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <Servo.h>
#define right_track A4
#define left_track A5
#define trig A2
#define echo A3
#define right_obstacle A0
#define left_obstacle A1
#define trig2 2
#define echo2 9


/* another version of the avoid obstacle robot, more accurate but much slower
   due to the bad accuracy of the hc-sr04, hc srf05,.. when the angle is more than 25 degree
   this one uses only one hc-sr04 with a servo motor sg90 to check left and right too. */

// initialize the motors and the servo motor

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_64KHZ);
Servo myservo;


long duration;
int how_far;
int where_am_i;
int where_am_i2;
int where_am_i3;
int pos;
bool right;
bool left;
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
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
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
      myservo.write(25);
      where_am_i2 = distance1();
      delay(1500);
      myservo.write(125);
      where_am_i3 = distance1();
      delay(1500);
      myservo.write(77);
      where_am_i = distance1();
      delay(1000);
    if (where_am_i > 25 && where_am_i3 > 25 && where_am_i2 > 25) {
      forward();
      delay(500);
      freeze();
    }
    else
    {
      freeze();
      delay(1000);
      backward();
      delay(100);
      pivot_right();
      delay(300);
      freeze();
     }
}



void loop() {
  avoid_obstacle();
}

