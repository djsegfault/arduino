/*
  Pin.h - LightBrightLib - Library for controlling lights.
  Created by David Kramer.
  Released into the public domain.
  
  Base class that interfaces with a input or output pin
*/
#ifndef Pin_h
#define Pin_h

#include "Arduino.h"

#define PIN_MIN_VALUE 0
#define PIN_MAX_VALUE 100

class Pin
{
  public:
  	Pin();
    Pin(int pin);
    void setPin(int pin);
    int getPin();
    void setValue(int value);
    int getValue();
    void on();
    void off();
    void setMock(boolean value);
    void setDebug(boolean value);
    int getMock();
    int getDebug();
  protected:
    int _pin;
    int _value;
    boolean _isDebug;
    boolean _isMock;
    // This method is child-specific. It's empty in this base class
    void _setPinValue(int value);
};

#endif

