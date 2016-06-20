#include "Arduino.h"
#include "Logging.h"

#include "Pin.h"

void Pin::begin(int pinNumber) {
	pinMode(pinNumber, OUTPUT);
	_pinNumber = pinNumber;
	setMock(false);
}

int Pin::getPinNumber() {
	return _pinNumber;
}	

void Pin::setValue(int value) {
	_value = value;
	
	Log.Verbose("Pin.SetValue %d --> %d mocked=%d"CR, _pinNumber, value, _isMock);	
	if(! _isMock) {
		setPinValue(value);
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

void Pin::setMock(boolean value) {
	_isMock = value;
}

int Pin::getMock() {
	return _isMock;
} 







