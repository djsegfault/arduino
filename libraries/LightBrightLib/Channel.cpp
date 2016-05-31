#include "Arduino.h"
#include "Logging.h"

#include "Channel.h"
#include "Pin.h"

Channel::Channel() {
	setMasterLevel(PIN_MAX_VALUE);
}

Channel::Channel(Pin pin) : Channel() {
	setPin(pin);
}

void Channel::setNumber(int channelNumber) {
	_channelNumber = channelNumber;
}

int Channel::getNumber() {
	return _channelNumber;
}

void Channel::setPin(Pin pin) {
	_pin = pin;
}

Pin Channel::getPin() {
	return _pin;
}

void Channel::setLevel(int level) {
	_level = level;
	_updateEffectiveLevel();
}

int Channel::getLevel() {
	return _level;
}

void Channel::on() {
	_level = PIN_MAX_VALUE;
	_updateEffectiveLevel();
}

void Channel::off() {
	_level = PIN_MIN_VALUE;
	_updateEffectiveLevel();
}

void Channel::toggle() {
	if(_level != PIN_MAX_VALUE) {
		on();
	} else {
		off();
	}
}

void Channel::setMasterLevel(int level) {
	_masterLevel = level;
	_updateEffectiveLevel();
}
	

void Channel::_updateEffectiveLevel() {	
	float divisor = (float) (PIN_MAX_VALUE - PIN_MIN_VALUE);
	_effectiveLevel = (int) (_level * ( (float) _masterLevel / divisor ) );
	
	Log.Debug("Channel %d pin %d level=%d master=%d effective=%d"CR, _channelNumber, _pin.getPinNumber(), _level, _masterLevel, _effectiveLevel);
	_pin.setValue(_effectiveLevel);
}

