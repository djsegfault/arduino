#include "Arduino.h"
#include "DigitalOutPin.h"

DigitalOutPin::DigitalOutPin(int pin) {
	_pin = pin;
}

void DigitalOutPin::set(int value) {
	if(_isDebug) {
		String message = "DigitalOutPin ";
		message = message + _pin;
		message = message + " -> " ;
		message = message + _value ;
		message = message + "\n";
		Serial.println(message);
	}
	
	if(! _isMock) {
		_value = value;
		digitalWrite(_pin, value);
	}
		
}	

void DigitalOutPin::on() {
	set(HIGH);
}

void DigitalOutPin::off() {
	set(LOW);
}

void DigitalOutPin::setMock(boolean value) {
	_isMock = value;
	if(_isMock) {
		  Serial.begin(9600);
	}
}

void DigitalOutPin::setDebug(boolean value) {
	_isDebug = value;
}






