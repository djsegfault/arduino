/*
  DigitalOutPin.h - Library for controlling lights.
  Created by David Kramer.
  Released into the public domain.
*/
#ifndef DigitalOutPin_h
#define DigitalOutPin_h

#include "Arduino.h"

class DigitalOutPin
{
  public:
    DigitalOutPin(int pin);
    void set(int value);
    int get();
    void on();
    void off();
    void setMock(boolean value);
    void setDebug(boolean value);
    int getMock();
    int getDebug();
  private:
    int _pin;
    int _value;
    boolean _isDebug;
    boolean _isMock;
};

#endif

