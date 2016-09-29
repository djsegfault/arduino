/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright

  Channel.h
  This is the abstract Channel class that enables all the channel types to be
  in one collection, like an array.  It also defines all the common functionality.
*/

#ifndef Channel_h
#define Channel_h

#include "Arduino.h"
#include <Logging.h>
#include "Pin.h"

class Channel
{
  public:
    Channel();
    void begin(Pin *pin, int channelNumber, Channel *masterChannel);
    int getNumber();
    Pin* getPin();
    void setLevel(int level);
    int getLevel();
    void on();
    void off();
    void toggle();
  protected:
  	int _channelNumber;
    Pin *_pin;
    Channel *_masterChannel;
    int _level;
    int _effectiveLevel;
    void _updateEffectiveLevel();
};

#endif


