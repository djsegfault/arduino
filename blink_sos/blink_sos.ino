/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
#define PIN 13
#define DOT_DELAY 100
#define DASH_DELAY 500
#define CHAR_DELAY 300
#define END_DELAY 3000

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(13, OUTPUT);    
}

void loop() {
  dot();
  dot();
  dot();
  dash();
  dash();
  dash();
  dot();
  dot();
  dot();
  delay(END_DELAY);
}

void dot() {
  digitalWrite(PIN, HIGH);
  delay(DOT_DELAY);
  digitalWrite(13, LOW);
  delay(CHAR_DELAY);
}

void dash() {
  digitalWrite(PIN, HIGH);
  delay(DASH_DELAY);
  digitalWrite(PIN, LOW);
  delay(CHAR_DELAY);
}


