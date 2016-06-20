/*
 DigitalOutPin.h - LightBrightLibrary for controlling lights.
 Created by David Kramer.
 Released into the public domain.
 */
#ifndef DigitalOutPin_h
#define DigitalOutPin_h

#include "Arduino.h"
#include "Pin.h"

class DigitalOutPin: public Pin {
public:
protected:
	void setPinValue(int value);
};

#endif
