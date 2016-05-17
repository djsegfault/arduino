#include "Arduino.h"
#include "Channel.h"
#include "Pin.h"

Channel::Channel() {
	setMasterLevel(100);
}

Channel::Channel(Pin pin) : Channel() {
	setPin(pin);
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

void Channel::setMasterLevel(int level) {
	_masterLevel = level;
	_updateEffectiveLevel();
}
	

void Channel::_updateEffectiveLevel() {	
	float divisor = (float) (PIN_MAX_VALUE - PIN_MIN_VALUE);
	_effectiveLevel = (int) (_level * ( (float) _masterLevel / divisor ) );
	
	/*
		For debugging this calculation
		Serial.print("updateEffectiveLevel(): master=");
		Serial.print(_masterLevel);
		Serial.print("  divisor=");
		Serial.print(divisor);
		Serial.print(" level=");
		Serial.print( _level);
		Serial.print(" effective=");
		Serial.println(_effectiveLevel);
	*/
	
	_pin.setValue(_effectiveLevel);
}

