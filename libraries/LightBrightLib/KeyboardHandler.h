/*
  KeyboardHandler.h - LightBrightLib - Library for controlling lights.
  Created by David Kramer.
  Released into the public domain.
  
  Handles input from PS/2 keyboard
  Expects configurable declarations to be done in LightBrightConfig.h
*/
#ifndef KeyboardHandler_h
#define KeyboardHandler_h

#include "Arduino.h"
#include "LightBrightConfig.h"
#include "PS2Keyboard.h"
#include "Channel.h"


class KeyboardHandler
{
	public:
		void begin(Channel *digitalChannels);
		bool handleKeyboard();
		bool handleKey(char key);
	protected:
		Channel *_digitalChannels;
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
