/*
http://arduino.cc/en/Tutorial/SerialCallResponse
*/

// these constant variables store the pin numbers
const int ledPin = 9;
const int knobPin = 0;

int inByte = 0;         // incoming serial byte

void setup()  {
  // initialize the serial port
  Serial.begin(9600);
  Serial.print("Command: ");
}

void loop()  {
  inByte = Serial.read();
  
  if(inByte > 0) {
    // print the input value to the serial port for debugging
    String message = "Got a ";
    
    message += inByte;
    Serial.println(message);
    Serial.print("Command: ");
  }
  
  delay(500);
}

