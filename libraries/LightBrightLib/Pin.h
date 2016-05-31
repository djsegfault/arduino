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
#define PIN_MAX_VALUE 255

class Pin
{
  public:
  	Pin();
    Pin(int pinNumber);
    void setPinNumber(int pinNumber);
    int getPinNumber();
    void setValue(int value);
    int getValue();
    void on();
    void off();
    void setMock(boolean value);
    int getMock();
  protected:
    int _pinNumber;
    int _value;
    boolean _isMock;
    
    // This method is child-specific. It's empty in this base class
    virtual void _setPinValue(int value);
};

#endif

