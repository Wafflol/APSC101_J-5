#include <Servo.h>

Servo myServo;

const int trigPin = 10;
const int echoPin = 11;
const int servo = 9;
int pos = 0;
long duration;
int distance;
int toggle = 1;
long timeSinceToggle = 10000;
bool alreadyUp = true;
long timeSinceUp = 10000;
int minDist = 4;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(servo);
  myServo.write(0);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  delay(100);
}

void loop() {
  //sends ultrasonic signal
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //calculates distance using signal
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  
  //checks if sensor is minDist or less away from the ground, and if claw was not recently toggled
  //also checks if claw has gone back up yet to prevent claw opening while ascending (in the second if statement)
  if(distance < minDist && millis() - timeSinceToggle > 4000 && millis() - timeSinceUp > 2000 && alreadyUp == true){
    //toggles servo between 180 and 0
    myServo.write(180 * (toggle % 2));
    timeSinceToggle = millis();
    toggle++;
    delay(100);
    alreadyUp = false;
  }
  if(alreadyUp == false && distance > 10){
    timeSinceUp = millis();
    alreadyUp = true;
  }

  //for debugging
  Serial.print("Distance: ");
  Serial.println(distance);
  
}
