#include <Servo.h>
#include <Arduino.h>

Servo myservo;  
int servoPos = 180;  // Variable to store the servo position

int stepPin = 3;    // Stepper motor's step pin
int dirPin = 2;     // Stepper motor's direction pin
int stepsPerRevolution = 4096; // Original step count
int stepsFor72Degrees = 819;   // Step count per 72 degrees

int pushButton = 6; // Button connected to pin 6
unsigned long lastTriggerTime = 0;  // Record the last trigger time
const unsigned long triggerInterval = 5000;  // Event trigger interval, 5000ms (5 seconds)
int lastButtonState = LOW; // Record the last button state

int ledPin = 8; // LED connected to pin 8

void setup() {
  myservo.attach(9);  // Attach the servo to pin 9
  pinMode(ledPin, OUTPUT);  // Set the LED pin as output
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  digitalWrite(dirPin, LOW); // Set the rotation direction for the stepper motor
  digitalWrite(stepPin, LOW);
  Serial.begin(9600); // Set the baud rate to 9600 bits per second
  pinMode(pushButton, INPUT); // Set the pushButton as INPUT
}

void loop() {
  int buttonState = digitalRead(pushButton); // Read the voltage state of the pushButton
  unsigned long currentTime = millis();

  if (buttonState == HIGH && lastButtonState == LOW && (currentTime - lastTriggerTime > triggerInterval)) {
    lastTriggerTime = currentTime; // Update the last trigger time
    lastButtonState = HIGH; // Update the button state record

    digitalWrite(ledPin, HIGH); // Turn on the LED
    // Servo control code
    for (servoPos = 180; servoPos >= 0; servoPos--) {
      myservo.write(servoPos);
      delay(15);
    }
    for (servoPos = 0; servoPos <= 180; servoPos++) {
      myservo.write(servoPos);
      delay(15);
    }
    digitalWrite(ledPin, LOW); // Turn off the LED

    int multiplier = random(3, 10); // Generate a random number between 3 and 10

    for (int i = 0; i < stepsFor72Degrees * multiplier; i++) {
      digitalWrite(stepPin, HIGH);
      delay(1);
      digitalWrite(stepPin, LOW);
      delay(1);
    }
    delay(1000);  // Stop for one second after a random multiple of 72 degrees
  } else if (buttonState == LOW) {
    lastButtonState = LOW; // Update the button state record, indicating the wire has been separated
  }
  delay(15); // Control the loop speed and response time
}