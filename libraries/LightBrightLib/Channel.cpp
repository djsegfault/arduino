/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright

  Channel.cpp
  This is the abstract Channel class that enables all the channel types to be
  in one collection, like an array.  It also defines all the common functionality.
*/


#include "Arduino.h"
#include "Logging.h"

#include "Channel.h"
#include "Pin.h"

Channel::Channel() {
}


void Channel::begin(Pin *pin, int channelNumber, Channel *masterChannel) {
	_pin = pin;
	_channelNumber = channelNumber;
	_masterChannel = masterChannel;
	_level = PIN_MIN_VALUE;
}

int Channel::getNumber() {
	return _channelNumber;
}

Pin* Channel::getPin() {
	return _pin;
}

void Channel::setLevel(int level) {
	_level = level;
	_updateEffectiveLevel();
}

int Channel::getLevel() {
	return _level;
}

void Channel::on() {
	_level = PIN_MAX_VALUE;
	_updateEffectiveLevel();
}

void Channel::off() {
	_level = PIN_MIN_VALUE;
	_updateEffectiveLevel();
}

void Channel::toggle() {
	if(_level != PIN_MAX_VALUE) {
		on();
	} else {
		off();
	}
}

void Channel::_updateEffectiveLevel() {	
	float divisor = (float) (PIN_MAX_VALUE - PIN_MIN_VALUE);
	_effectiveLevel = (int) (_level * ( (float) _masterChannel->getLevel() / divisor ) );
	
	Log.Debug("Channel %d pin %d level=%d master=%d effective=%d"CR, 
			_channelNumber, 
			_pin->getPinNumber(), 
			_level, 
			_masterChannel->getLevel(), 
			_effectiveLevel);
	_pin->setValue(_effectiveLevel);
}

