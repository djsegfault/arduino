/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright

  Pin.cpp
  Base class that interfaces with a input or output pin
*/

#include "Pin.h"

void Pin::begin(int pinNumber) {
	_pinNumber = pinNumber;
	pinMode(_pinNumber, OUTPUT);
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
	setValue(LBPIN_MAX_VALUE);
}

void Pin::off() {
	setValue(LBPIN_MIN_VALUE);
}

void Pin::setMock(boolean value) {
	_isMock = value;
}

int Pin::getMock() {
	return _isMock;
} 







