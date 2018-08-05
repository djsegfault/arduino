/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright

  Pin.h  
  Base class that interfaces with a input or output pin
*/

#ifndef Pin_h
#define Pin_h

#include "Arduino.h"
#include "Logging.h"

#define PIN_MIN_VALUE 0
#define PIN_MAX_VALUE 255

class Pin
{
  public:
    void begin(int pinNumber);
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
    virtual void setPinValue(int value)=0;
};

#endif

