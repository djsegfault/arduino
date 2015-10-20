#include "Servo.h"

#define PIN_IN  A5
#define PIN_SERVO_OUT 3

Servo myServo;

void setup() {
  pinMode(PIN_IN, INPUT);
  myServo.attach(PIN_SERVO_OUT);
  Serial.begin(9600);

}

void loop() {
  int reading = analogRead(PIN_IN);
  Serial.print(reading);
  Serial.print("   ");
  int position = reading / 8;
  Serial.println(position);
  myServo.write(position);
  // Or int po3=map(reading ,....
}
