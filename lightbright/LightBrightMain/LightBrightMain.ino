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
#include "AnalogOutPin.h"
#include "Channel.h"
#include "KeyboardHandler.h"
#include "SerialHandler.h"
#include "LightBoard.h"

#include <Logging.h>

#define LOGLEVEL LOG_LEVEL_DEBUG

// Globals
LightBoard lightBoard;

DigitalOutPin digitalPins[LBPIN_DOUT_COUNT];
AnalogOutPin analogPins[LBPIN_AOUT_COUNT];
DigitalOutPin masterPin;

Channel channels[LBCHANNEL_COUNT];
Channel masterChannel;


#ifdef LBC_KEYBOARD
KeyboardHandler keyboardHandler;
#endif
SerialHandler serialHandler;

void setup() {
	Log.Init(LOGLEVEL, 9600L);
	delay(1000);
	Log.Info(CR"LightBrightMain starting"CR);
  int nextChannel = 0;

  //Initialize master
  masterPin.begin(LBPIN_DOUT_MASTER);
  masterChannel.begin(&masterPin, 99, &masterChannel);
  Log.Info("Initialized master channel %d to pin %d"CR, masterChannel.getNumber(), masterChannel.getPin()->getPinNumber());
  masterChannel.on();

  // Initialize digital outputs
  for (int x = 0; x < LBPIN_DOUT_COUNT; x++) {
    digitalPins[x].begin(LBPIN_DOUT_START + (x * LBPIN_DOUT_INTERVAL));
    channels[nextChannel].begin(&digitalPins[x], nextChannel+1, &masterChannel);
    Log.Info("Initialized digital channel %d to pin %d"CR, channels[nextChannel].getNumber(), channels[nextChannel].getPin()->getPinNumber());
    nextChannel++;
  }
  
  // Initialize analog outputs
  for (int x = 0; x < LBPIN_AOUT_COUNT; x++) {
    analogPins[x].begin(LBPIN_AOUT_START + (x * LBPIN_AOUT_INTERVAL));
    channels[nextChannel].begin(&analogPins[x], nextChannel+1, &masterChannel);
    Log.Info("Initialized analog channel %d to pin %d"CR, channels[nextChannel].getNumber(), channels[nextChannel].getPin()->getPinNumber());
    nextChannel++;
  }

	lightBoard.begin(channels, &masterChannel);


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



