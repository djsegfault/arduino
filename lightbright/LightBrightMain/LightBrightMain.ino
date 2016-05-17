
#include <DigitalOutPin.h>



DigitalOutPin outPin(25); 

void setup() {
  Serial.begin(9600);
  Serial.println("Init");
  outPin.setMock(false);
  outPin.setDebug(true);

}

void loop() {
  outPin.setMock(! outPin.getMock() );
  outPin.on();
  delay(1000);
  outPin.off();
  delay(1000);

}
