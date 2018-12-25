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

