/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright
  
  KeyboardHandler.h
  Handles input from PS/2 keyboard
  Expects configurable declarations to be done in LightBrightConfig.h
*/

#ifndef KeyboardHandler_h
#define KeyboardHandler_h

#include "Arduino.h"
#include "Logging.h"
#include "LightBrightConfig.h"
#include "LightBoard.h"
#include "PS2Keyboard.h"
#include "Channel.h"


class KeyboardHandler
{
	public:
		void begin(LightBoard *lightBoard);
		char checkKeyboard();
		bool handleKey(char key);
	protected:
		void clearMomentary(int x);
		LightBoard *_lightBoard;
		PS2Keyboard _keyboard;
		char _momentaryKeys[LBCHANNEL_COUNT]=LBKEY_MOMENTARY;   // Needed so we can treat it as a char array
		char _toggleKeys[LBCHANNEL_COUNT]=LBKEY_TOGGLE;         // Needed so we can treat it as a char array
		char _momentaryMasterKey=LBKEY_MASTER_MOMENTARY;
		char _toggleMasterKey=LBKEY_MASTER_TOGGLE;
		
		bool _momentaryStatus[LBCHANNEL_COUNT];
		bool _toggleStatus[LBCHANNEL_COUNT];
		bool _momentaryMasterStatus;
		bool _toggleMasterStatus;
};
		
#endif
