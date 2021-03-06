/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright
  
  AnalogOutPin.cpp
  Analog output pin handler, parent is Pin
*/
 
#include "AnalogOutPin.h"
#include <Logging.h>

// For analog, we can send 0-255
void AnalogOutPin::setPinValue(int value) {
	int safeValue;

	Log.Verbose("AnalogOutPin CALLED"CR);
	
	if(value < LBPIN_MIN_VALUE) {
		safeValue = LBPIN_MIN_VALUE;
	} else if(value > LBPIN_MAX_VALUE) {
		safeValue = LBPIN_MAX_VALUE;
	} else {
		safeValue = value;
	}
		
	Log.Verbose("AnalogOutPin %d -> %d -> %d"CR, _pinNumber,value, safeValue);
	analogWrite(_pinNumber, safeValue);
}


