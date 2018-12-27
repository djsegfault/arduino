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
	Log.Verbose("DigitalOutPin CALLED"CR);
	if(value == LBPIN_MIN_VALUE) {
		Log.Verbose("DigitalOutPin %d -> %d -> HIGH"CR, value, _pinNumber);
		digitalWrite(_pinNumber, LOW);
	} else {
		Log.Verbose("DigitalOutPin %d -> %d -> LOW"CR, value, _pinNumber);
		digitalWrite(_pinNumber, HIGH);
	}
}


