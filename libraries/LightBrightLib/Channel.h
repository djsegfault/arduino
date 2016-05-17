/*
  Channel.h - LightBrightLib - Library for controlling lights.
  Created by David Kramer.
  Released into the public domain.
  
  This is the abstract Channel class that enables all the channel types to be
  in one collection, like an array.  It also defines all the common functionality.
*/

#ifndef Channel_h
#define Channel_h

#include "Arduino.h"
#include "Pin.h"

class Channel
{
  public:
    Channel();
    Channel(Pin pin);
    void setPin(Pin pin);
    Pin getPin();
    void setLevel(int level);
    int getLevel();
    void on();
    void off();
    void setMasterLevel(int level);
  protected:
    Pin _pin;
    int _level;
    int _masterLevel;
    int _effectiveLevel;
    void _updateEffectiveLevel();
};

#endif

