/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright
  
  KeyboardHandler.cpp
  Handles input from PS/2 keyboard
  Expects configurable declarations to be done in LightBrightConfig.h
*/

#include "LightBrightConfig.h"
#include "KeyboardHandler.h"

void KeyboardHandler::begin(LightBoard *lightBoard) {
	_lightBoard = lightBoard;
	_keyboard.begin(LBPIN_KBD_DATA, LBPIN_KBD_IRQ);

	for(int x=0; x<LBCHANNEL_COUNT; x++) {
		_momentaryStatus[x] = false;
		_toggleStatus[x] = false;
	}
	_momentaryMasterStatus = false;
	_toggleMasterStatus = false;
}

char KeyboardHandler::checkKeyboard() {
	Log.Verbose("[KeyboardHandler] Looking for key"CR);
	char key = 0;
	if (_keyboard.available()) {
		key = _keyboard.read();
	}

	return key;
}

bool KeyboardHandler::handleKey(char key) {
	Log.Debug("[KeyboardHandler] Got key '%c' "CR, key);
	bool keyFound=false;
	
	// Is it a channel key?
	for(int x=0; x< LBCHANNEL_COUNT; x++) {
		if(key == _momentaryKeys[x]) {
			// Is it a momentary digital key?
			keyFound=true;
			if(_momentaryStatus[x] == false) {
				_lightBoard->getChannel(x)->on();
				_momentaryStatus[x] = true;
				Log.Debug("[KeyboardHandler] Momentary on '%d'"CR, _lightBoard->getChannel(x)->getNumber());
			} else {
				Log.Verbose("[KeyboardHandler] Momentary already on '%d'"CR, _lightBoard->getChannel(x)->getNumber());
			}
		} else if(key == _toggleKeys[x]) {
			// Is it a toggle digital key?
			keyFound=true;
			Log.Debug("[KeyboardHandler] toggling '%d'"CR, _lightBoard->getChannel(x)->getNumber());
			_lightBoard->getChannel(x)->toggle();
		} else {
			// If this channel's keys are not being pressed, turn it off if it's on.
			Log.Verbose("[KeyboardHandler] Momemtary not being pressed, so clearing '%d'"CR, _lightBoard->getChannel(x)->getNumber());
			clearMomentary(x);
		}
	}
	
	if(! keyFound && key == LBKEY_MASTER_MOMENTARY) {
		keyFound=true;
		if(_momentaryMasterStatus == false) {
			_lightBoard->getMasterChannel()->on();
			_momentaryMasterStatus = true;
			Log.Debug("[KeyboardHandler] Momentary on Master"CR);
		} else {
			Log.Verbose("[KeyboardHandler] Momentary Master already on"CR);
		}
	}

	if(! keyFound && key == LBKEY_MASTER_TOGGLE) {
		keyFound=true;
		Log.Debug("[KeyboardHandler] toggling Master"CR);
		_lightBoard->getMasterChannel()->toggle();
	}
	
	
	if(! keyFound) {
		Log.Error("[KeyboardHandler] Unidentified key '%c' (%d)"CR, key, key);
	}
	
	return keyFound;
}

void KeyboardHandler::clearMomentary(int x) {
	if(_momentaryStatus[x] == true) {
		_lightBoard->getChannel(x)->off();
		_momentaryStatus[x] = false;
		Log.Debug("[KeyboardHandler] Momentary off '%d'"CR, _lightBoard->getChannel(x)->getNumber());
	}
}
