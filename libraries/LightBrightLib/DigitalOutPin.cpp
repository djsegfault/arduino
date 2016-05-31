
#include "Arduino.h"
#include "Logging.h"
#include "DigitalOutPin.h"

DigitalOutPin::DigitalOutPin() {
}

DigitalOutPin::DigitalOutPin(int pinNumber) : Pin(pinNumber) {
}

// For Digital, it's just on or off
void DigitalOutPin::_setPinValue(int value) {
	Log.Verbose("DigitalOutPin %d -> %d"CR, _pinNumber,value);
	if(value == PIN_MIN_VALUE) {
		digitalWrite(_pinNumber, LOW);
	} else {
		digitalWrite(_pinNumber, HIGH);
	}
		
}

void DigitalOutPin::on() {
	setValue(HIGH);
}

void DigitalOutPin::off() {
	setValue(LOW);
}

