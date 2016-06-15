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

void KeyboardHandler::handleKeyboard() {
	 if (_keyboard.available()) {
		char c = _keyboard.read();
		handleKey(c);
	 }
}
	
bool KeyboardHandler::handleKey(int key) {
	Log.Debug("Got key '%c'"CR, key);
	bool keyFound=false;
	
	for(int x=0; x<LBPIN_DOUT_COUNT; x++) {
		if(key == _momentaryDOutKeys[x]) {
			keyFound=true;
			if(_momentaryDOutStatus[x] == false) {
				_digitalChannels[x].on();
				_momentaryDOutStatus[x] = true;
			}
		} else if(key == _toggleDOutKeys[x]) {
			keyFound=true;
			_digitalChannels[x].toggle();
		}
	}
	
	return keyFound;
}

