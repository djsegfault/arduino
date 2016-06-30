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
		bool handleKeyboard();
		bool handleKey(char key);
	protected:
		void clearMomentary(int x);
		LightBoard *_lightBoard;
		PS2Keyboard _keyboard;
		char _momentaryDOutKeys[LBPIN_DOUT_COUNT]=LBKEY_DOUT_MOMENTARY;
		char _toggleDOutKeys[LBPIN_DOUT_COUNT]=LBKEY_DOUT_TOGGLE;
		char _momentaryMasterKey=LBKEY_MASTER_MOMENTARY;
		char _toggleMasterKey=LBKEY_MASTER_TOGGLE;
		
		bool _momentaryDOutStatus[LBPIN_DOUT_COUNT];
		bool _toggleDOutStatus[LBPIN_DOUT_COUNT];
		bool _momentaryMasterStatus;
		bool _toggleMasterStatus;
};
		
#endif
