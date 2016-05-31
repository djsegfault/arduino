/*
  DigitalOutPin.h - LightBrightLibrary for controlling lights.
  Created by David Kramer.
  Released into the public domain.
*/
#ifndef DigitalOutPin_h
#define DigitalOutPin_h

#include "Arduino.h"
#include "Pin.h"

class DigitalOutPin : public Pin
{
  public:
    DigitalOutPin();
    DigitalOutPin(int pinNumber);
    void on();
    void off();
  protected:
  	void _setPinValue(int value);
};

#endif

