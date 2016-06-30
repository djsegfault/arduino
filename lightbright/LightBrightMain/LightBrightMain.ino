/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright
  
  LightBrightMain.ino
  Main lighting board program using LightBrightLib
*/

// Third-party headers
#include <PS2Keyboard.h>


// LightBright headers
#include "LightBrightConfig.h"
#include "DigitalOutPin.h"
#include "Channel.h"
#include "KeyboardHandler.h"
#include "SerialHandler.h"
#include "LightBoard.h"

#include <Logging.h>

#define LOGLEVEL LOG_LEVEL_DEBUG

// Globals
LightBoard lightBoard;

Channel masterChannel;

Channel digitalChannels[LBPIN_DOUT_COUNT];
DigitalOutPin digitalPins[LBPIN_DOUT_COUNT];


#ifdef LBC_KEYBOARD
KeyboardHandler keyboardHandler;
#endif
SerialHandler serialHandler;

void setup() {
	Log.Init(LOGLEVEL, 9600L);
	delay(1000);
	Log.Info(CR"LightBrightMain starting"CR);

	// Initialize digital outputs
	for (int x = 0; x < LBPIN_DOUT_COUNT; x++) {
		digitalPins[x].begin(LBPIN_DOUT_START + (x * LBPIN_DOUT_INTERVAL));
		digitalChannels[x].begin(&digitalPins[x], x+1);
		Log.Info("Initialized digital channel %d to pin %d"CR, digitalChannels[x].getNumber(), digitalChannels[x].getPin()->getPinNumber());
	}

	lightBoard.begin(digitalChannels, digitalChannels, &masterChannel);


#ifdef LBC_KEYBOARD
	keyboardHandler.begin(&lightBoard);
#endif
	serialHandler.begin(&lightBoard);


}

void loop() {

#ifdef LBC_KEYBOARD
	keyboardHandler.handleKeyboard();
	serialHandler.handleSerial();
#endif

}



