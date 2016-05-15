#include "Arduino.h"
#include "DigitalOutPin.h"

DigitalOutPin::DigitalOutPin(int pin) {
	_pin = pin;
	pinMode(pin, OUTPUT);
}

void DigitalOutPin::set(int value) {
	_value = value;
	if(_isDebug) {
		String message = "DigitalOutPin ";
		message = message + _pin;
		message = message + " -> " ;
		message = message + _value ;
		if( _isMock) {
			message = message + " (MOCKED)";
		}
		
		Serial.println(message);
	}
	
	if(! _isMock) {
		digitalWrite(_pin, value);
	}
		
}	

int DigitalOutPin::get() {
	return _value;
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

int DigitalOutPin::getMock() {
	return _isMock;
} 

void DigitalOutPin::setDebug(boolean value) {
	_isDebug = value;
}

int DigitalOutPin::getDebug() {
	return _isDebug;
}






