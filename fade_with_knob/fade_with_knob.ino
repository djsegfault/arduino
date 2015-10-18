/*
  http://www.andrewfrueh.com/electronics/?pageContent=fade_LED_with_knob.html
  Use a knob to fade an LED.
 
  This super simple script allows you to use a potentiometer (knob) to control the brightness of an LED.
  We use analogRead() to get the value from the control knob.
  We use analogWrite() to set the brightness of the LED.
 
  Important note: the analog inputs on the Arduino (Duemillanove +) have 10 bit resolution, while the digital pins (PWM) are only 8 bit resolution. So analogRead() will be 0 to 1023, while analogWrite() will be 0 to 254.
 
  The circuit:
  * LED attached from digital pin 9 to ground.
  * Control knob (potentiometer) with the center leg connected to analog pin 0, and the outer two legs connected to ground and source voltage respectivly.
 
 
  created 2010
  by Andrew Frueh
 
  I built this code starting with "Fading" from Arduino examples - 1 Nov 2008, By David A. Mellis
  http://arduino.cc/en/Tutorial/Fading
*/

// these constant variables store the pin numbers
const int ledPin = 9;
const int knobPin = 0;

// these variables store the values for the knob and LED level
int knobValue, fadeValue;

void setup()  {
  // initialize the serial port
  Serial.begin(9600);
}

void loop()  {
  // read the value from the input
  knobValue = analogRead(knobPin);
  // remap the values from 10 bit input to 8 bit output
  fadeValue = map(knobValue, 0, 900, 0 , 254);
  // use the input value to fade the led
  analogWrite(ledPin, fadeValue);
  
  // print the input value to the serial port for debugging
  String message = "knob='";
 message += knobValue;
 message += "' fade='"; 
 message += fadeValue;
 message += "'";
  Serial.println(message);
  delay(500);
  analogWrite(ledPin, 0);
  delay(500);
}

