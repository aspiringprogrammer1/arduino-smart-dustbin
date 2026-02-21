#include <Servo.h>

// Define Pins
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;
const int greenLed = 3;
const int redLed = 2;

// Variables
long duration;
int distance;
Servo myServo;

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(9600);
  
  // Pin Modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  
  // Attach Servo
  myServo.attach(servoPin);
  myServo.write(0); // Start closed
  digitalWrite(redLed, HIGH); // Red LED on (Closed)
}

void loop() {
  // 1. Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // 2. Set the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // 3. Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // 4. Calculate the distance
  // Formula: Distance = (Time * SpeedOfSound) / 2
  // Speed of sound is approx 0.034 cm/microsecond
  distance = duration * 0.034 / 2;
  
  // 5. Logic Control
  if (distance < 20 && distance > 0) {
    Serial.println("ACTION: Opening Lid!");
    openLid();
  } else {
    closeLid();
  }
  
  // Debugging (Required for report)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(100);
}

void openLid() {
  myServo.write(90); // Rotate to 90 degrees (Open)
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);
  delay(3000); // Keep open for 3 seconds
}

void closeLid() {
  myServo.write(0); // Rotate back to 0 degrees (Closed)
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, HIGH);
}