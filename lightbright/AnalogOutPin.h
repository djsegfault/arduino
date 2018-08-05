/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright

  DigitalOutPin.h
  Digital output pin handler, parent is Pin
*/
 
#ifndef AnalogOutPin_h
#define AnalogOutPin_h

#include "Arduino.h"
#include "Logging.h"
#include "Pin.h"

class AnalogOutPin: public Pin {
public:
protected:
	void setPinValue(int value);
};

#endif
