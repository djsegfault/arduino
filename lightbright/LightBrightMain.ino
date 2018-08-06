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
#include "BluetoothHandler.h"
#include "SerialHandler.h"
#include "RGBOutput.h"
#include "LightBoard.h"

#include <Logging.h>

// Globals
LightBoard lightBoard;

DigitalOutPin digitalPins[LBPIN_DOUT_COUNT];
AnalogOutPin analogPins[LBPIN_AOUT_COUNT];
DigitalOutPin masterPin;

Channel channels[LBCHANNEL_COUNT];
Channel masterChannel;

RGBOutput rgb;

// Key to channel mappings
char momentaryKeys[LBCHANNEL_COUNT]=LBKEY_MOMENTARY;   // Needed so we can treat it as a char array
char toggleKeys[LBCHANNEL_COUNT]=LBKEY_TOGGLE;         // Needed so we can treat it as a char array
char momentaryMasterKey=LBKEY_MASTER_MOMENTARY;
char toggleMasterKey=LBKEY_MASTER_TOGGLE;

// Key statuses
bool momentaryStatus[LBCHANNEL_COUNT];
bool toggleStatus[LBCHANNEL_COUNT];
bool momentaryMasterStatus;
bool toggleMasterStatus;

#ifdef LBC_KEYBOARD
KeyboardHandler keyboardHandler;
#endif
SerialHandler serialHandler;

BluetoothHandler bluetoothHandler;

// Used for building commands
char commandBuffer[LB_COMMAND_MAX_LENGTH];

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
    channels[nextChannel].off();
    Log.Info("Initialized digital channel %d to pin %d"CR, channels[nextChannel].getNumber(), channels[nextChannel].getPin()->getPinNumber());
    nextChannel++;
  }
  
  // Initialize analog outputs
  for (int x = 0; x < LBPIN_AOUT_COUNT; x++) {
    analogPins[x].begin(LBPIN_AOUT_START + (x * LBPIN_AOUT_INTERVAL));
    channels[nextChannel].begin(&analogPins[x], nextChannel+1, &masterChannel);
    channels[nextChannel].off();
    Log.Info("Initialized analog channel %d to pin %d"CR, channels[nextChannel].getNumber(), channels[nextChannel].getPin()->getPinNumber());
    nextChannel++;
  }

  // Initialize key states
  for (int x = 0; x < LBCHANNEL_COUNT; x++) {
	  momentaryStatus[x] = false;
	  toggleStatus[x] = false;
  }
  momentaryMasterStatus = false;
  toggleMasterStatus = false;

  rgb.begin(LBPIN_RGB_RED, LBPIN_RGB_GREEN, LBPIN_RGB_BLUE);

  lightBoard.begin(channels, &masterChannel);


#ifdef LBC_KEYBOARD
	keyboardHandler.begin(&lightBoard);
#endif
	serialHandler.begin(&lightBoard);
	bluetoothHandler.begin();

	// Initialize command buffer
	commandBuffer[0]=NULL;


}

int handleKey(char key) {
	Log.Debug("Got key '%c' "CR, key);
	bool keyFound=false;

	// Are we building a command? Or is the the command start key?
	if(commandBuffer[0] != 0 || key == LBKEY_COMMAND_START) {
		if(strlen(commandBuffer) < LB_COMMAND_MAX_LENGTH) {
			commandBuffer[strlen(commandBuffer)] = key;
			commandBuffer[strlen(commandBuffer) + 1] = NULL;
			Log.Debug("Command is now '%s'"CR, commandBuffer);

			if(key == LBKEY_COMMAND_END) {
				handleCommand();
			}
		} else {
			Log.Error("Command '%s' to long, abandoning"CR, commandBuffer);
			commandBuffer[0] =  NULL;
		}
		keyFound=true;
	} else {

		// Is it a channel key?
		for(int x=0; x< LBCHANNEL_COUNT; x++) {
			if(key == momentaryKeys[x]) {
				// Is it a momentary digital key?
				keyFound=true;
				if(momentaryStatus[x] == false) {
					lightBoard.getChannel(x)->on();
					momentaryStatus[x] = true;
					Log.Debug("[KeyboardHandler] Momentary on '%d'"CR, lightBoard.getChannel(x)->getNumber());
				} else {
					Log.Verbose("[KeyboardHandler] Momentary already on '%d'"CR, lightBoard.getChannel(x)->getNumber());
				}
			} else if(key == toggleKeys[x]) {
				// Is it a toggle digital key?
				keyFound=true;
				Log.Debug("[KeyboardHandler] toggling '%d'"CR, lightBoard.getChannel(x)->getNumber());
				lightBoard.getChannel(x)->toggle();
			} else {
				// If this channel's keys are not being pressed, turn it off if it's on.
				Log.Verbose("[KeyboardHandler] Momemtary not being pressed, so clearing '%d'"CR, lightBoard.getChannel(x)->getNumber());
				clearMomentaryKey(x);
			}
		}

		if(! keyFound && key == LBKEY_MASTER_MOMENTARY) {
			keyFound=true;
			if(momentaryMasterStatus == false) {
				lightBoard.getMasterChannel()->on();
				momentaryMasterStatus = true;
				Log.Debug("[KeyboardHandler] Momentary on Master"CR);
			} else {
				Log.Verbose("[KeyboardHandler] Momentary Master already on"CR);
			}
		}

		if(! keyFound && key == LBKEY_MASTER_TOGGLE) {
			keyFound=true;
			Log.Debug("[KeyboardHandler] toggling Master"CR);
			lightBoard.getMasterChannel()->toggle();
		}
	}


	if(! keyFound) {
		Log.Error("[KeyboardHandler] Unidentified key '%c' (%d)"CR, key, key);
	}

	return keyFound;
}

void handleCommand() {
	Log.Info("Processing command '%s'"CR, commandBuffer);
	commandBuffer[0] = NULL;
}

void clearMomentaryKey(int x) {
	if(momentaryStatus[x] == true) {
		lightBoard.getChannel(x)->off();
		momentaryStatus[x] = false;
		Log.Debug("[KeyboardHandler] Momentary off '%d'"CR, lightBoard.getChannel(x)->getNumber());
	}
}



void loop() {
	char key;

#ifdef LBC_KEYBOARD
	key = keyboardHandler.checkKeyboard();
	if(key != 0) {
		handleKey(key);
	} else {
		// If no key is pressed, clear all momentary keys
		for(int x=0; x<LBCHANNEL_COUNT; x++) {
			clearMomentaryKey(x);
		}
	}
	key = bluetoothHandler.checkBluetooth();
	if(key != 0) {
		handleKey(key);
		bluetoothHandler.sendMessage("Got key from BT");
	}
	serialHandler.handleSerial();
#endif

}



