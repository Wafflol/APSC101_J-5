#include <Servo.h>
#include <NewPing.h>

NewPing sonar(10, 11, 200);
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
int minDist = 20;
int red = 5;
int green = 2;
int yellow = 7;
int downtime = 4000;
int openAngle = 90;

void blink() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(yellow, HIGH);
    delay(500);
    digitalWrite(yellow, LOW);
    delay(500);
  }
}

void goToAngle(int ang) {
  if (pos <= ang) {
    for ( ; pos <= ang; pos++) {
      myServo.write(pos);
      delay(4);
    }
  }
  if (pos > ang) {
    for ( ; pos >= ang; pos--) {
      myServo.write(pos);
      delay(4);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  myServo.attach(servo);
  myServo.write(0);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  Serial.begin(9600);
  delay(100);
}

void loop() {
  //sends ultrasonic signal
  //digitalWrite(trigPin, LOW);
  //delayMicroseconds(2);
  //digitalWrite(trigPin, HIGH);
  //delayMicroseconds(10);
  //digitalWrite(trigPin, LOW);

  //calculates distance using signal
  //duration = pulseIn(echoPin, HIGH);
  //distance = duration * 0.034 / 2;

  distance = sonar.ping_cm();

  //checks if sensor is minDist or less away from the ground, and if claw was not recently toggled
  //also checks if claw has gone back up yet to prevent claw opening while ascending (in the second if statement)
  if (distance < minDist && distance != 0 && millis() - timeSinceToggle > downtime && millis() - timeSinceUp > 2000 && alreadyUp == true) {
    //toggles servo between 180 and 0
    if (openAngle == pos) {
      blink();
    }
    //myServo.write(openAngle * (toggle % 2));
    int angleToGo = openAngle * (toggle % 2);
    goToAngle(angleToGo);

    pos = (openAngle * (toggle % 2));
    timeSinceToggle = millis();
    toggle++;
    delay(100);
    alreadyUp = false;
  }
  if (alreadyUp == false && distance > minDist) {
    timeSinceUp = millis();
    alreadyUp = true;
  }


  if (millis() - timeSinceToggle < downtime) {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
  }
  else if (millis() - timeSinceToggle > downtime && millis() - timeSinceUp > 2000 && alreadyUp) {
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
  }
  if (millis() - timeSinceToggle > downtime) {
    digitalWrite(yellow, HIGH);
  }


  //for debugging
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(60);
}
