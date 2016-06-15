#include "Arduino.h"
#include "Logging.h"

#include "KeyboardHandler.h"

void KeyboardHandler::begin(Channel *digitalChannels) {
	_digitalChannels = digitalChannels;
	_keyboard.begin(LBPIN_KBD_DATA, LBPIN_KBD_IRQ);

	for(int x=0; x<LBPIN_DOUT_COUNT; x++) {
		_momentaryDOutStatus[x] = false;
		_toggleDOutStatus[x] = false;
	}
	_momentaryMasterStatus = false;
	_toggleMasterStatus = false;
}

bool KeyboardHandler::handleKeyboard() {
	
	 if (_keyboard.available()) {
		char c = _keyboard.read();
		return handleKey(c);
	 } else {
	 	 // If nothing is pressed, turn off any momentary keys 
	 	 for(int x=0; x<LBPIN_DOUT_COUNT; x++) {
			if(_momentaryDOutStatus[x] == true) {
				_digitalChannels[x].off();
				_momentaryDOutStatus[x] = false;
				Log.Debug("[KeyboardHandler] Momentary off '%d'"CR, x);
			}
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
				_digitalChannels[x].on();
				_momentaryDOutStatus[x] = true;
				Log.Debug("[KeyboardHandler] Momentary on '%d'"CR, x);
			} else {
				Log.Debug("[KeyboardHandler] Momentary already on '%d'"CR, x);
			}
		} else if(key == _toggleDOutKeys[x]) {
		// Is it a toggle digital key?
			keyFound=true;
			Log.Debug("[KeyboardHandler] toggling '%d'"CR, x);
			_digitalChannels[x].toggle();
		}  
	}
	
	
	
	return keyFound;
}

