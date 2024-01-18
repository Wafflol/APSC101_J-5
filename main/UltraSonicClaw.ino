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
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  //timeSinceUp does not work im shooting myself
  if(distance < 4 && millis() - timeSinceToggle > 4000 && millis() - timeSinceUp > 2000){
    Serial.print("moved");
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
  
  Serial.print("Distance: ");
  Serial.println(distance);
  
}
