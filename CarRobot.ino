#include "Servo.h"
const int ENA = 5;
const int IN1 = 7 ;
const int IN2 = 8;
const int ENB = 6;
const int IN3 = 9;
const int IN4 = 11;
const int ECHO = A4;
const int TRIG = A5;
Servo labservo;
const int servoPin = 3;
int servoPos = 90;
float duration = 0; //duration ECHO is HIGH

//remote control
#include <IRremote.h>
#define RECV_PIN 12 //Infrared signal receiving pin
#define LED 13 //define LED pin
#define L 16720605
#define R 16761405
#define F 16736925
#define B 16754775
#define UNKNOWN_L 1386468383
#define UNKNOWN_R 553536955
#define UNKNOWN_F 5316027
#define UNKNOWN_B 2747854299
bool state = LOW; //define default input mode
unsigned long val;
IRrecv irrecv(RECV_PIN); //initialization
decode_results results; //Define structure type

//prototype
void MoveForward(int speed);
void MoveBackward(int speed);
void stopMoving();
void turnLeft(int speed);
void turnRight(int speed);
void stateChange();

void stateChange(){
  
}

float measureDistance(){
  digitalWrite(TRIG , LOW);
  delay(5);
  digitalWrite(TRIG, HIGH);
  delay(5);
  digitalWrite(TRIG, LOW);
  
  duration = pulseIn(ECHO, HIGH); //measures the time the ECHO is HIGH
  float distance_cm = duration /50;
  return distance_cm;
}

void MoveForward(int speed){

  analogWrite(ENA,speed);
  analogWrite(ENB,speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
}

void MoveBackward(int speed){
  analogWrite(ENA,speed);
  analogWrite(ENB,speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMoving(){
  //Motor direction irrelevant.
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0); //Set Motor A Speed to 0
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 0); //Set Motor B speed to 0
  
}

void turnLeft(int speed) //Function for the robot to turn to the left
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
}

void turnRight(int speed) //Function for the robot to turn to the left
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(ENA, OUTPUT); 
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(ENB, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
  pinMode(TRIG,OUTPUT); //set TRIG to output
  pinMode(ECHO, INPUT); //set ECHO to input
  labservo.attach(servoPin);//attaching the servo to the servoPinoutput
  labservo.write(servoPos); 
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start receiving
}

void loop() {
  // put your main code here, to run repeatedly:
  float distance_cm = measureDistance();
    if(distance_cm <= 15){
      stopMoving();
      delay(1000);
      MoveBackward(128);
      delay(500);
      stopMoving();
      labservo.write(180);//left
      delay(1000);
      float left = measureDistance();
    // Serial.println("left " + (String)left);
      labservo.write(0);//right
      delay(1000);
      float right = measureDistance();
      //Serial.println("right" + (String)right);
      labservo.write(90); //middle
      delay(1500);
      if(right > left){
      turnRight(128);
      }
      else{
       turnLeft(128);
      }
      delay(1000);
    }
  stopMoving();
  
  if(irrecv.decode(&results)){

     val = results.value;
     Serial.println(val);
     irrecv.resume(); // Receive the next value
     delay(150);

    
    

    if(val == L || val == UNKNOWN_L ){
      turnLeft(128);
      delay(1000);
    }

    if(val == R || val == UNKNOWN_R){
      turnRight(128);
      delay(1000);
    }

    if(val == F || val == UNKNOWN_F){
      MoveForward(128);
      delay(1000);
    }

    if(val == B || val == UNKNOWN_B){
      MoveBackward(128);
      delay(1000);
    }
  }
  
  
  
  
}
