#include "Arduino.h"
#include "DigitalOutPin.h"

DigitalOutPin::DigitalOutPin() {
}

DigitalOutPin::DigitalOutPin(int pin) : Pin(pin) {
	pinMode(pin, OUTPUT);
}

// For Digital, it's just on or off
void DigitalOutPin::_setPinValue(int value) {
	if(value == 0) {
		digitalWrite(_pin, LOW);
	} else {
		digitalWrite(_pin, HIGH);
	}
		
}

void DigitalOutPin::on() {
	setValue(HIGH);
}

void DigitalOutPin::off() {
	setValue(LOW);
}

