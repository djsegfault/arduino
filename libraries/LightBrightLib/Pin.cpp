#include "Arduino.h"
#include "Pin.h"

Pin::Pin() {
}

Pin::Pin(int pin) {
	_pin = pin;
}

void Pin::setPin(int pin) {
	_pin = pin;
}

int Pin::getPin() {
	return _pin;
}	

void Pin::setValue(int value) {
	_value = value;
	
	if(_isDebug) {
		String message = "Pin ";
		message = message + _pin;
		message = message + " -> " ;
		message = message + _value ;
		if( _isMock) {
			message = message + " (MOCKED)";
		}
		
		Serial.println(message);
	}
	
	if(! _isMock) {
		_setPinValue(value);
	}		
}	

int Pin::getValue() {
	return _value;
}

void Pin::on() {
	setValue(PIN_MAX_VALUE);
}

void Pin::off() {
	setValue(PIN_MIN_VALUE);
}

void Pin::_setPinValue(int value) {
	// This method is child-specific. It's empty in this base class
}

void Pin::setMock(boolean value) {
	_isMock = value;
}

int Pin::getMock() {
	return _isMock;
} 

void Pin::setDebug(boolean value) {
	_isDebug = value;
}

int Pin::getDebug() {
	return _isDebug;
}






