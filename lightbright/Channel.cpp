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
	_pin = 0;
	_channelNumber = 0;
	_masterChannel = NULL;
	_level = LBPIN_MIN_VALUE;
	_effectiveLevel = LBPIN_MIN_VALUE;
}


void Channel::begin(Pin *pin, int channelNumber, Channel *masterChannel) {
	_pin = pin;
	_channelNumber = channelNumber;
	_masterChannel = masterChannel;
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
	_level = LBPIN_MAX_VALUE;
	_updateEffectiveLevel();
}

void Channel::off() {
	_level = LBPIN_MIN_VALUE;
	_updateEffectiveLevel();
}

int Channel::isOn() {
	if(_level == LBPIN_MAX_VALUE)  {
		return true;
	} else {
		return false;
	}
}

int Channel::isOff() {
	if(_level == LBPIN_MIN_VALUE)  {
		return true;
	} else {
		return false;
	}
}

void Channel::toggle() {
	if(_level != LBPIN_MAX_VALUE) {
		on();
	} else {
		off();
	}
}

void Channel::_updateEffectiveLevel() {	
	_effectiveLevel = (int) (_level * ( (float) _masterChannel->getLevel() / LBPIN_VALUE_STEPS ) );
	
	Log.Debug("[Chan] Num %d Pin %d [%d->%d]"CR,
			_channelNumber, 
			_pin->getPinNumber(), 
			_level, 
			_effectiveLevel);
	_pin->setValue(_effectiveLevel);
}

