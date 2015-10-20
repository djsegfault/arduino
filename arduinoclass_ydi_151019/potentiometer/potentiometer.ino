// Turn a pot to adjust LED brightness

#define PIN_IN  A5
#define PIN_OUT 11

void setup() {
  pinMode(PIN_IN, INPUT);
  pinMode(PIN_OUT, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  int reading = analogRead(PIN_IN);
  Serial.println(reading);

  //adjustBrightness(reading);

  adjustDelay(reading);
}

void adjustBrightness(int reading) {
  // Analog input 0-1023, analog output 0-255 so we have to scale
  int brightness = reading / 4;
  analogWrite(PIN_OUT, brightness);  
}

void adjustDelay(int reading) {
  // Analog input 0-1023, analog output 0-255 so we have to scale
  int delayMS = reading;
  analogWrite(PIN_OUT, 255);
  delay(delayMS);
  analogWrite(PIN_OUT, 0);
  delay(delayMS);
}





