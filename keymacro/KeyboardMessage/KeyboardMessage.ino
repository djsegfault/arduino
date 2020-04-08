/*
  Keyboard Message test

  For the Arduino Leonardo and Micro.

  Sends a text string when a button is pressed.

  The circuit:
  - pushbutton attached from pin 4 to +5V
  - 10 kilohm resistor attached from pin 4 to ground

  created 24 Oct 2011
  modified 27 Mar 2012
  by Tom Igoe
  modified 11 Nov 2013
  by Scott Fitzgerald

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/KeyboardMessage
*/

#include "Keyboard.h"

const int buttonPin = 0;          // input pin for pushbutton
int previousButtonState = HIGH;   // for checking the state of a pushButton

const int switchCount = 4;
int prevButtonState[] = {0,0,0,0};


void checkButton(int buttonNumber, void (*handler)(int) ){
  int buttonState = digitalRead(buttonNumber);
  if(buttonState == HIGH &&  prevButtonState[buttonNumber] == LOW) {
    Serial.print("Button ");
    Serial.print(buttonNumber);
    Serial.println(" pressed");
    (*handler)(buttonNumber);
    
  }
  prevButtonState[buttonNumber] = buttonState;
}


void setup() {
  Serial.begin(115200);
  // make the pushButton pin an input:
  pinMode(buttonPin, INPUT);
  pinMode(1, INPUT);
  // initialize control over the keyboard:
  Keyboard.begin();

}

void genericHandler(int buttonNumber) {
  Keyboard.print("You pressed the button ");
  Keyboard.println(buttonNumber);
}

void loop() {
  checkButton(0,&genericHandler);
  checkButton(1,&genericHandler);
  
}

void oldloop() {
  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  // if the button state has changed,
  if ((buttonState != previousButtonState)
      // and it's currently pressed:
      && (buttonState == HIGH)) {
    Serial.println("Is now HIGH");
    delay(5000);
    // type out a message
    Keyboard.print("You pressed the button ");
    Keyboard.println(" times.");
  }
  // save the current button state for comparison next time:
  previousButtonState = buttonState;
  delay(1000);
}
