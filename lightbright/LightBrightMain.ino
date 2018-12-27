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

Sequencer sequencer;
int sequenceChannelNumbers[SEQ_BANKS][SEQ_STEPS] = SEQ_CHANNEL_NUMBERS;
Channel *sequenceChannels[SEQ_BANKS][SEQ_STEPS];


// Key to channel mappings
char momentaryKeys[LBCHANNEL_COUNT] = LBKEY_MOMENTARY; // Needed so we can treat it as a char array
char toggleKeys[LBCHANNEL_COUNT] = LBKEY_TOGGLE; // Needed so we can treat it as a char array
char momentaryMasterKey = LBKEY_MASTER_MOMENTARY;
char toggleMasterKey = LBKEY_MASTER_TOGGLE;

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
	Log.Init(LOG_LEVEL_DEBUG, 115200L);
	delay(1000);
	Log.Info(CR"LightBrightMain starting"CR);
	int nextChannel = 0;

	//Initialize master
	masterPin.begin(LBPIN_DOUT_MASTER);
	masterChannel.begin(&masterPin, 99, &masterChannel);
	Log.Info("Initialized master channel %d to pin %d"CR,
			masterChannel.getNumber(), masterChannel.getPin()->getPinNumber());
	masterChannel.on();

	// Initialize digital outputs
	for (int x = 0; x < LBPIN_DOUT_COUNT; x++) {
		digitalPins[x].begin(LBPIN_DOUT_START + (x * LBPIN_DOUT_INTERVAL));
		// Channel number is 1-based not 0-based
		channels[nextChannel].begin(&digitalPins[x], nextChannel + 1,
				&masterChannel);
		channels[nextChannel].off();
		Log.Info("Initialized digital channel %d (element %d) to pin %d"CR,
				channels[nextChannel].getNumber(),
				nextChannel,
				channels[nextChannel].getPin()->getPinNumber());
		nextChannel++;
	}

	// Initialize analog outputs
	for (int x = 0; x < LBPIN_AOUT_COUNT; x++) {
		analogPins[x].begin(LBPIN_AOUT_START + (x * LBPIN_AOUT_INTERVAL));
		channels[nextChannel].begin(&analogPins[x], nextChannel + 1,
				&masterChannel);
		channels[nextChannel].off();
		Log.Info("Initialized analog channel %d to pin %d"CR,
				channels[nextChannel].getNumber(),
				channels[nextChannel].getPin()->getPinNumber());
		nextChannel++;
	}

	// Initialize key states
	for (int x = 0; x < LBCHANNEL_COUNT; x++) {
		momentaryStatus[x] = false;
		toggleStatus[x] = false;
	}
	momentaryMasterStatus = false;
	toggleMasterStatus = false;

	rgb.begin(LBPIN_RGB_RED, LBPIN_RGB_GREEN, LBPIN_RGB_BLUE, &masterChannel);

	// Initialize Sequencer
	// Always load bank 0 by default
	for(int bank=0; bank < SEQ_BANKS; bank++) {
		for(int step=0; step < SEQ_STEPS; step++) {
			if(sequenceChannelNumbers[bank][step] >= 0 && sequenceChannelNumbers[bank][step] < LBCHANNEL_COUNT) {
				sequencer.setChannel(bank, step, &channels[ sequenceChannelNumbers[bank][step] ]);
			} else {
				sequencer.setChannel(bank, step, NULL);
			}
		}
	}
	sequencer.setBank(0);
	sequencer.begin(&rgb);

	lightBoard.begin(channels, &masterChannel, &rgb);

#ifdef LBC_KEYBOARD
	keyboardHandler.begin(&lightBoard);
#endif
	serialHandler.begin();
	bluetoothHandler.begin();

	commandBuffer[0] = 0;
	Log.Info("Setup done"CR);
	Log.Info(CR);
	Log.Info(CR);
}

void handleKey(char key) {
	// Ignore certain keys like CR/LF
	if(key == 13 || key == 10) {
		return;
	}

	Log.Verbose("[Key] Got '%c' "CR, key);
	bool keyFound = false;

	// Are we building a command? Or is the the command start key?
	if (commandBuffer[0] != 0 || key == LBKEY_COMMAND_START) {
		Log.Verbose("Adding to command, first char is %d length=%d Command before is '%s'"CR,
				commandBuffer[0], strlen(commandBuffer), commandBuffer);
		if (strlen(commandBuffer) < LB_COMMAND_MAX_LENGTH) {
			commandBuffer[strlen(commandBuffer)] = key;
			commandBuffer[strlen(commandBuffer) + 1] = NULL;
			Log.Verbose("Command is now '%s'"CR, commandBuffer);

			if (key == LBKEY_COMMAND_END) {
				handleCommand();
			}
		} else {
			Log.Error("Command '%s' too long, abandoning"CR, commandBuffer);
			commandBuffer[0] = NULL;
		}
		keyFound = true;
	} else {
		// Is it a channel key?
		for (int x = 0; x < LBCHANNEL_COUNT; x++) {
			if (key == momentaryKeys[x]) {
				// Is it a momentary digital key?
				keyFound = true;
				if (momentaryStatus[x] == false) {
					lightBoard.getChannel(x)->on();
					momentaryStatus[x] = true;
					Log.Debug("[Key] Momentary on '%d'"CR,
							lightBoard.getChannel(x)->getNumber());
				} else {
					Log.Verbose("[Key] Momentary already on '%d'"CR,
							lightBoard.getChannel(x)->getNumber());
				}
			} else if (key == toggleKeys[x]) {
				// Is it a toggle digital key?
				keyFound = true;
				Log.Debug("[Key] toggling '%d'"CR,
						lightBoard.getChannel(x)->getNumber());
				lightBoard.getChannel(x)->toggle();
			} else {
				// If this channel's keys are not being pressed, turn it off if it's on.
				Log.Verbose(
						"[Key] Momentary not being pressed, so clearing '%d'"CR,
						lightBoard.getChannel(x)->getNumber());
				clearMomentaryKey(x);
			}
		}

		if (!keyFound && key == LBKEY_MASTER_MOMENTARY) {
			keyFound = true;
			if (momentaryMasterStatus == false) {
				lightBoard.getMasterChannel()->on();
				momentaryMasterStatus = true;
				Log.Debug("[Key] Momentary on Master"CR);
			} else {
				Log.Verbose("[Key] Momentary Master already on"CR);
			}
		}

		if (!keyFound && key == LBKEY_MASTER_TOGGLE) {
			keyFound = true;
			Log.Debug("[Key] toggling Master"CR);
			lightBoard.getMasterChannel()->toggle();
		}

		// Is it a sequencer key?
		if (!keyFound && key == LBKEY_SEQ_TOGGLE) {
			keyFound = true;
			sequencer.toggle();
		}
		if (!keyFound && key == LBKEY_SEQ_MARK) {
			keyFound = true;
			sequencer.markTime();
		}

	}

	if (!keyFound) {
		Log.Error("[Key] Unidentified key '%c' (%d)"CR, key, key);
	}
}

void handleCommand() {
	Log.Info("Processing command '%s'"CR, commandBuffer);
	switch(commandBuffer[1]) {
	case 'B':
		handleBluetoothCommand();
		break;
	case 'M':
		handleMasterCommand();
		break;
	case 'R': // RGBOutout
		handleRGBCommand();
		break;
	case 'S':
		handleSequenceCommand();
		break;
	case 'T':
		handleTextCommand();
		break;
	default:
		Log.Error("Invalid command '%s'"CR, commandBuffer);
		break;
	}

	// Clear the buffer after command is processed
	// Initialize command buffer
	for (int x = 0; commandBuffer[x] != 0; x++) {
		commandBuffer[x] = 0;
	}

}


void handleBluetoothCommand() {
	switch (commandBuffer[2]) {
	case 'R':  // Reconnect
		bluetoothHandler.begin();
		break;
	default:
		Log.Error("Invalid Bluetooth command"CR);
		break;
	}
}

void handleMasterCommand() {
	switch (commandBuffer[2]) {
	case '0':  // Off
		masterChannel.setLevel(PIN_MIN_VALUE);
		break;
	case '1':  // Set level
		masterChannel.setLevel(PIN_MAX_VALUE);
		break;
	case 'T':  // Set level
		masterChannel.toggle();
		break;
	case 'L':  // Set level
		// TODO really parse level
		masterChannel.setLevel(50);
		break;
	default:
		Log.Error("Invalid master level command "CR);
		break;
	}
}

void handleRGBCommand() {
	switch(commandBuffer[2]) {
		case 'M':
			switch(commandBuffer[3]) {
			case 'N':
				rgb.setMode(RGBOutput::NONE);
				break;
			case 'M':
				rgb.setMode(RGBOutput::MUSIC);
				break;
			case 'S':
				rgb.setMode(RGBOutput::SEQUENCE_RGB);
				break;
			case 'R':
				rgb.setMode(RGBOutput::SEQUENCE_RANDOM);
				break;
			default:
				Log.Error("Invalid RGB mode command"CR);
				break;
			}
			break;
		case 'C':
			switch(commandBuffer[3]) {
			case 'K':
				rgb.setColor(RGBOutput::BLACK);
				break;
			case 'R':
				rgb.setColor(RGBOutput::RED);
				break;
			case 'G':
				rgb.setColor(RGBOutput::GREEN);
				break;
			case 'B':
				rgb.setColor(RGBOutput::BLUE);
				break;
			case 'P':
				rgb.setColor(RGBOutput::PURPLE);
				break;
			case 'Y':
				rgb.setColor(RGBOutput::YELLOW);
				break;
			case 'W':
				rgb.setColor(RGBOutput::WHITE);
				break;
			default:
				Log.Error("Invalid RGB color command"CR);
				break;
			}
			break;
		default:
			Log.Error("Invalid RGB command"CR);
			break;
	}
}

void handleSequenceCommand() {
	int newBank;
	switch(commandBuffer[2]) {
	case 'B':
		newBank = commandBuffer[3] - '0';
		if(newBank >=0 && newBank < SEQ_BANKS) {
			sequencer.setBank(newBank);
		} else {
			Log.Error("Invalid bank '%c'"CR, newBank);
		}
		break;
	case '0':
		sequencer.off();
		break;
	case '1':
		sequencer.on();
		break;
	case 'T':
		sequencer.toggle();
		break;
	case 'M':
		sequencer.markTime();
		break;
	default:
		Log.Error("Invalid sequence command");
		break;
	}
}

void handleTextCommand() {
	Log.Info("Message: %s"CR, (commandBuffer + 2) );
}

void clearMomentaryKey(int x) {
	if (momentaryStatus[x] == true) {
		lightBoard.getChannel(x)->off();
		momentaryStatus[x] = false;
		Log.Debug("[KeyboardHandler] Momentary off '%d'"CR,
				lightBoard.getChannel(x)->getNumber());
	}
}

void loop() {
	char key;

#ifdef LBC_KEYBOARD
	key = keyboardHandler.checkKeyboard();
	if (key != 0) {
		handleKey(key);
	} else {
		// If no key is pressed, clear all momentary keys
		for (int x = 0; x < LBCHANNEL_COUNT; x++) {
			clearMomentaryKey(x);
		}
	}
#endif

	key = bluetoothHandler.checkBluetooth();
	if (key != 0) {
		handleKey(key);
	}

	key = serialHandler.checkSerial();
	if (key != 0) {
		handleKey(key);
	}

	// Update objects
	rgb.update();
	sequencer.update();
}

