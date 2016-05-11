#include "Arduino.h"
#include "DigitalOutPin.h"

DigitalOutPin::DigitalOutPin(int pin) {
	_pin = pin;
}



void DigitalOutPin::set(int value) {
	_value = value;
	digitalWrite(_pin, value);
}

void DigitalOutPin::on() {
	set(HIGH);
}

void DigitalOutPin::off() {
	set(LOW);
}

void DigitalOutPin::setMock(boolean value) {
	_isMock = value;
}

void DigitalOutPin::setDebug(boolean value) {
	_isDebug = value;
}






