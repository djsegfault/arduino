/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright

  LightBoard.cpp
  This is the container that holds all the LightBoards and other controls.
  I created this class because it saves from passing in all the individual
  objects to things like the KeyboardHandler.  Before this, they all had to
  be passed in individually, and every time there was a new object, the
  parameters to begin() would have to change to pass them in.
  
*/

#include "LightBoard.h"

void LightBoard::begin(Channel *channels, Channel *masterChannel)
{
	_channels = channels;
	_masterChannel = masterChannel;
}

void LightBoard::on() 
{
	_masterChannel->on();
}

void LightBoard::off() 
{
	_masterChannel->off();
}

Channel * LightBoard::getMasterChannel()
{
	return _masterChannel;
}

Channel * LightBoard::getChannel(int channelNumber)
{
	return &_channels[channelNumber];
}


	