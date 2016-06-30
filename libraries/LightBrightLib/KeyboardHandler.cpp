/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright
  
  KeyboardHandler.cpp
  Handles input from PS/2 keyboard
  Expects configurable declarations to be done in LightBrightConfig.h
*/

#include "KeyboardHandler.h"

void KeyboardHandler::begin(LightBoard *lightBoard) {
	_lightBoard = lightBoard;
	_keyboard.begin(LBPIN_KBD_DATA, LBPIN_KBD_IRQ);

	for(int x=0; x<LBPIN_DOUT_COUNT; x++) {
		_momentaryDOutStatus[x] = false;
		_toggleDOutStatus[x] = false;
	}
	_momentaryMasterStatus = false;
	_toggleMasterStatus = false;
}

bool KeyboardHandler::handleKeyboard() {
	//Log.Verbose("[KeyboardHandler] Looking for key"CR);
	if (_keyboard.available()) {
		char c = _keyboard.read();
		return handleKey(c);
	} else {
		// If nothing is pressed, turn off any momentary keys
		for(int x=0; x<LBPIN_DOUT_COUNT; x++) {
			clearMomentary(x);
		}
	}
}

bool KeyboardHandler::handleKey(char key) {
	Log.Debug("[KeyboardHandler] Got key '%c'"CR, key);
	bool keyFound=false;

	// Is it a digital channel key?
	for(int x=0; x<LBPIN_DOUT_COUNT; x++) {
		if(key == _momentaryDOutKeys[x]) {
			// Is it a momentary digital key?
			keyFound=true;
			if(_momentaryDOutStatus[x] == false) {
				_lightBoard->getDigitalChannel(x)->on();
				_momentaryDOutStatus[x] = true;
				Log.Debug("[KeyboardHandler] Momentary on '%d'"CR, x);
			} else {
				Log.Verbose("[KeyboardHandler] Momentary already on '%d'"CR, x);
			}
		} else if(key == _toggleDOutKeys[x]) {
			// Is it a toggle digital key?
			keyFound=true;
			Log.Debug("[KeyboardHandler] toggling '%d'"CR, x);
			_lightBoard->getDigitalChannel(x)->toggle();
		} else {
			// If this digital key is not being pressed, turn it off if it's on.
			clearMomentary(x);
		}
	}

	return keyFound;
}

void KeyboardHandler::clearMomentary(int x) {
	if(_momentaryDOutStatus[x] == true) {
		_lightBoard->getDigitalChannel(x)->off();
		_momentaryDOutStatus[x] = false;
		Log.Debug("[KeyboardHandler] Momentary off '%d'"CR, x);
	}
}
