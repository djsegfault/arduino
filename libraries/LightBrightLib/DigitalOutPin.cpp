/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright
  
  DigitalOutPin.cpp
  Digital output pin handler, parent is Pin
*/
 
#include "DigitalOutPin.h"

// For Digital, it's just on or off
void DigitalOutPin::setPinValue(int value) {
	Log.Verbose("DigitalOutPin %d -> %d"CR, _pinNumber,value);
	if(value == PIN_MIN_VALUE) {
		Log.Verbose("DigitalOutPin %d -> HIGH"CR, _pinNumber);
		digitalWrite(_pinNumber, LOW);
	} else {
	Log.Verbose("DigitalOutPin %d -> LOW"CR, _pinNumber);
		digitalWrite(_pinNumber, HIGH);
	}
}


