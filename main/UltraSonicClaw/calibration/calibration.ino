#include <Servo.h>
#include <NewPing.h>

NewPing sonar(10, 11, 200);
Servo myServo;

const int trigPin = 10;
const int echoPin = 11;
const int servo = 9;
int pos = 90;
long duration;
int distance;
int toggle = 1;
long timeSinceToggle = 10000;
bool alreadyUp = true;
long timeSinceUp = 10000;
int minDist = 20;
int red = 5;
int green = 2;
int yellow = 7;



void setup() {
  // put your setup code here, to run once:
  myServo.attach(servo);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  Serial.begin(9600);
  delay(100);
  myServo.write(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  int angle = Serial.read();
  Serial.print(angle);
  for (pos = 90; pos <= angle; pos += 1) { // goes from 0 degrees to 180 degrees
  // in steps of 1 degree
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(15);
  pos = angle;
}
