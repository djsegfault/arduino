/*
 * RGBOutput.cpp
 *
 * This code is designed to send PWM output to three channels to
 * control the red, green, and blue channels of RGB LED strips, controlled
 * via MOSFET transistors.
 *
 * The music mode uses two MSGEQ7 boards (one for left channel and one for right)
 * to return the current music level
 *
 *  Created on: Aug 5, 2018
 *      Author: David Kramer
 */

#include <Arduino.h>
#include <Logging.h>
#include "Pin.h"
#include "RGBOutput.h"

RGBOutput::RGBOutput() {
	_redPin = LBPIN_MIN_VALUE;
	_greenPin = LBPIN_MIN_VALUE;
	_bluePin = LBPIN_MIN_VALUE;
	_redLevel = LBPIN_MIN_VALUE;
	_greenLevel = LBPIN_MIN_VALUE;
	_blueLevel = LBPIN_MIN_VALUE;
	setMode(MUSIC);
}

RGBOutput::~RGBOutput() {
	// TODO Auto-generated destructor stub
}

void RGBOutput::begin(unsigned char redPin, unsigned char greenPin, unsigned char bluePin, Channel *masterChannel) {
	_redPin = redPin;
	_greenPin = greenPin;
	_bluePin = bluePin;
	_currentMode = NONE;
	_masterChannel = masterChannel;

	pinMode(_redPin, OUTPUT);
	pinMode(_greenPin, OUTPUT);
	pinMode(_bluePin, OUTPUT);

	analogWrite(_redPin, LBPIN_MIN_VALUE);
	analogWrite(_greenPin, LBPIN_MIN_VALUE);
	analogWrite(_bluePin, LBPIN_MIN_VALUE);

	/** @TODO Put a feature switch on sound **/
	pinMode(LBPIN_SOUND_RESET, OUTPUT);
	pinMode(LBPIN_SOUND_STROBE, OUTPUT);
	pinMode(LBPIN_SOUND_LEFT, INPUT);
	pinMode(LBPIN_SOUND_RIGHT, INPUT);
	digitalWrite(LBPIN_SOUND_RESET, LOW);
	digitalWrite(LBPIN_SOUND_STROBE, HIGH);
}

void RGBOutput::setLevels(int redLevel, int greenLevel, int blueLevel) {
	float masterLevelMultiplier = (float) _masterChannel->getLevel() / LBPIN_VALUE_STEPS;
	_redLevel   = constrain(redLevel   * masterLevelMultiplier, LBPIN_MIN_VALUE, LBPIN_MAX_VALUE) ;
	_greenLevel = constrain(greenLevel * masterLevelMultiplier, LBPIN_MIN_VALUE, LBPIN_MAX_VALUE);
	_blueLevel  = constrain(blueLevel  * masterLevelMultiplier, LBPIN_MIN_VALUE, LBPIN_MAX_VALUE);

	analogWrite(_redPin,   _redLevel);
	analogWrite(_greenPin, _greenLevel);
	analogWrite(_bluePin,  _blueLevel);

	Log.Debug("[RGB] [%d->%d][%d->%d][%d->%d]"CR,
			redLevel, _redLevel,
			greenLevel, _greenLevel,
			blueLevel, _blueLevel);
}

void RGBOutput::setColor(Color color) {
	Log.Info("[RGB] mode %d setColor %d"CR, _currentMode, color);

	switch(color) {
	case BLACK:
		setLevels(LBPIN_MIN_VALUE,LBPIN_MIN_VALUE,LBPIN_MIN_VALUE);
		break;
	case RED:
		setLevels(LBPIN_MAX_VALUE,LBPIN_MIN_VALUE,LBPIN_MIN_VALUE);
		break;
	case GREEN:
		setLevels(LBPIN_MIN_VALUE,LBPIN_MAX_VALUE,LBPIN_MIN_VALUE);
		break;
	case BLUE:
		setLevels(LBPIN_MIN_VALUE,LBPIN_MIN_VALUE,LBPIN_MAX_VALUE);
		break;
	case PURPLE:
		setLevels(LBPIN_MAX_VALUE,LBPIN_MIN_VALUE,LBPIN_MAX_VALUE);
		break;
	case YELLOW:
		setLevels(LBPIN_MAX_VALUE,LBPIN_MAX_VALUE,LBPIN_MIN_VALUE);
		break;
	case WHITE:
		setLevels(LBPIN_MAX_VALUE,LBPIN_MAX_VALUE,LBPIN_MAX_VALUE);
		break;
	}

}

RGBOutput::Mode RGBOutput::getMode() {
	return _currentMode;
}

void RGBOutput::setMode(Mode mode) {
	_currentMode = mode;

	if (_currentMode == NONE) {
		setLevels(LBPIN_MIN_VALUE, LBPIN_MIN_VALUE, LBPIN_MIN_VALUE);
	}

	Log.Info("RGB mode is now %d"CR, _currentMode);
}

void RGBOutput::update() {
	if (_currentMode == MUSIC) {
		updateMusic();
	} else {
		// Do nothing
	}
}

void RGBOutput::updateMusic() {
	digitalWrite(LBPIN_SOUND_RESET, HIGH);
	digitalWrite(LBPIN_SOUND_RESET, LOW);

	/**
	 * This algorithm takes the max of left and right for lowest, mid, and high band.
	 * It's kinda fragile to levels.  A better algorithm would take the differences
	 * between the levels so it would be less sensitive to absolute volume
	 */
	for (int i = 0; i < 7; i++) {
		digitalWrite(LBPIN_SOUND_STROBE, LOW);
		spectrumValueLeft[i] = analogRead(LBPIN_SOUND_LEFT);
		spectrumValueRight[i] = analogRead(LBPIN_SOUND_RIGHT);

		spectrumValueLeft[i] = map(spectrumValueLeft[i], 0, 1023, 0, 255);
		if (spectrumValueLeft[i] < LBSOUND_MINVALUE) {
			spectrumValueLeft[i] = LBPIN_MIN_VALUE;
		}
		spectrumValueRight[i] = map(spectrumValueRight[i], 0, 1023, 0, 255);
		if (spectrumValueRight[i] < LBSOUND_MINVALUE) {
			spectrumValueRight[i] = LBPIN_MIN_VALUE;
		}
		digitalWrite(LBPIN_SOUND_STROBE, HIGH);
	}

	Log.Verbose("RGBMusic: 0%d\t1 %d\t2 %d\t3 %d\t4 %d\t5 %d\t6 %d"CR,
			spectrumValueLeft[0],
			spectrumValueLeft[1],
			spectrumValueLeft[2],
			spectrumValueLeft[3],
			spectrumValueLeft[4],
			spectrumValueLeft[5],
			spectrumValueLeft[6]);

	setLevels(max(spectrumValueLeft[0], spectrumValueRight[0]),
				max(spectrumValueLeft[3], spectrumValueRight[3]),
				max(spectrumValueLeft[6], spectrumValueRight[6]) );
}
