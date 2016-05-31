#include "Arduino.h"
#include "Logging.h"

#include "Pin.h"

Pin::Pin() {
}

Pin::Pin(int pinNumber) : Pin(){
	setPinNumber(pinNumber);
	setMock(false);
}

void Pin::setPinNumber(int pinNumber) {
	pinMode(pinNumber, OUTPUT);
	_pinNumber = pinNumber;
}

int Pin::getPinNumber() {
	return _pinNumber;
}	

void Pin::setValue(int value) {
	_value = value;
	
	Log.Verbose("Pin.SetValue %d --> %d mocked=%d"CR, _pinNumber, value, _isMock);	
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
	// This method is child-specific.  It's virtual and must be overridden. 
	// It's empty in this base class
}

void Pin::setMock(boolean value) {
	_isMock = value;
}

int Pin::getMock() {
	return _isMock;
} 






