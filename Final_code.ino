//ARDUINO LINE FOLLOWING CAR OBSTACLE AVOIDING
 
//including the libraries
#include <AFMotor.h>
#include <NewPing.h>

#define TRIG_PIN A2
#define ECHO_PIN A3
#define MAX_DISTANCE 200 //sensor will detect obstacles upto 200 meters
#define MAX_SPEED 240 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20 //for debugging (not used)

//defining pins and variables
#define left A0
#define right A1

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

//defining motors
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {
  motor1.setSpeed(170);
  motor1.run(RELEASE);
  motor2.setSpeed(170);
  motor2.run(RELEASE);
  motor3.setSpeed(170);
  motor3.run(RELEASE);
  motor4.setSpeed(170);
  motor4.run(RELEASE);
  //declaring pin types
  pinMode(left,INPUT);
  pinMode(right,INPUT);
  //begin serial communication for print statements in serial monitor
  Serial.begin(9600);
  delay(1000);
}

void loop(){
  //-----------------------------
  distance = readPing();
  delay (100);
  if(distance<=15)
  {
    moveStop();
    delay(200);
    Serial.println("obstacle");
    delay(200);
  }
  else
  {
    moveForward();
  }

// both white
  if(digitalRead(left)==0 && digitalRead(right)==0){
    //Forward
    motor1.run(FORWARD);
    motor1.setSpeed(170);
    motor2.run(FORWARD);
    motor2.setSpeed(170);
    motor3.run(FORWARD);
    motor3.setSpeed(170);
    motor4.run(FORWARD);
    motor4.setSpeed(170);
  }
  //line detected by right sensor
  else if(digitalRead(left)==0 && digitalRead(right)==1){
    //turn right
    motor1.run(FORWARD);
    motor1.setSpeed(170);
    motor2.run(FORWARD);
    motor2.setSpeed(170);
    motor3.run(BACKWARD);
    motor3.setSpeed(170);
    motor4.run(BACKWARD);
    motor4.setSpeed(170);
  }
  //line detected by left sensor
  else if(digitalRead(left)==1 && digitalRead(right)==0){
    //turn left
    motor1.run(BACKWARD);
    motor1.setSpeed(170);
    motor2.run(BACKWARD);
    motor2.setSpeed(170);
    motor3.run(FORWARD);
    motor3.setSpeed(170);
    motor4.run(FORWARD);
    motor4.setSpeed(170);
  }

  //both black
  else if(digitalRead(left)==1 && digitalRead(right)==1){
    //stop
    motor1.run(RELEASE);
    motor1.setSpeed(0);
    motor2.run(RELEASE);
    motor2.setSpeed(0);
    motor3.run(RELEASE);
    motor3.setSpeed(0);
    motor4.run(RELEASE);
    motor4.setSpeed(0);
  }
}

int readPing() {
  delay(70);     //to ensure that the ultrasonic sensor gets enough time to measure the distance 0.07s
  int cm = sonar.ping_cm();   //measure the distance
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward() {
 if(!goesForward)
  {
    Serial.println("move forward");
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);    
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
   }
  }
}