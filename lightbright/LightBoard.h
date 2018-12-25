/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright

  LightBoard.h
  This is the container that holds all the LightBoards and other controls.
  I created this class because it saves from passing in all the individual
  objects to things like the KeyboardHandler.  Before this, they all had to
  be passed in individually, and every time there was a new object, the
  parameters to begin() would have to change to pass them in.
  
*/

#ifndef LightBoard_h
#define LightBoard_h

#include "Arduino.h"
#include <Logging.h>
#include "Sequencer.h"
#include "RGBOutput.h"
#include "Channel.h"

class LightBoard
{
public:
	void begin(Channel *channels, Channel *masterChannel, RGBOutput *rgb);
	void on();
	void off();
	Channel *getMasterChannel();
	Channel *getChannel(int channelNumber);
	RGBOutput *getRGB();
protected:
	Channel *_channels;
	Channel *_masterChannel;
	RGBOutput *_rgb;
};

#endif

