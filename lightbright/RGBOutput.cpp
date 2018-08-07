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

#include "Arduino.h"
#include "Logging.h"
#include "Pin.h"
#include "RGBOutput.h"

RGBOutput::RGBOutput() {
	_redPin = PIN_MIN_VALUE;
	_greenPin = PIN_MIN_VALUE;
	_bluePin = PIN_MIN_VALUE;
	_redLevel = PIN_MIN_VALUE;
	_greenLevel = PIN_MIN_VALUE;
	_blueLevel = PIN_MIN_VALUE;
	setMode(MUSIC);
}

RGBOutput::~RGBOutput() {
	// TODO Auto-generated destructor stub
}

void RGBOutput::begin(unsigned char redPin, unsigned char greenPin,
		unsigned char bluePin) {
	_redPin = redPin;
	_greenPin = greenPin;
	_bluePin = bluePin;

	pinMode(_redPin, OUTPUT);
	pinMode(_greenPin, OUTPUT);
	pinMode(_bluePin, OUTPUT);

	analogWrite(_redPin, PIN_MIN_VALUE);
	analogWrite(_greenPin, PIN_MIN_VALUE);
	analogWrite(_bluePin, PIN_MIN_VALUE);

	/** @TODO Put a feature switch on sound **/
	pinMode(LBPIN_SOUND_RESET, OUTPUT);
	pinMode(LBPIN_SOUND_STROBE, OUTPUT);
	pinMode(LBPIN_SOUND_LEFT, INPUT);
	pinMode(LBPIN_SOUND_RIGHT, INPUT);
	digitalWrite(LBPIN_SOUND_RESET, LOW);
	digitalWrite(LBPIN_SOUND_STROBE, HIGH);

}

void RGBOutput::RGBCurrentState(char* loopName) {
	/** TODO
	 * Switch this to use logging library
	 */
	Serial.print("RGB: ");
	Serial.print(loopName);
	Serial.print("\t");
	Serial.print(_redLevel);
	Serial.print("\t");
	Serial.print(_greenLevel);
	Serial.print("\t");
	Serial.println(_blueLevel);
}

void RGBOutput::setLevels(int redLevel, int greenLevel, int blueLevel) {
	if (_redLevel != redLevel) {
		_redLevel = constrain(redLevel, PIN_MIN_VALUE, PIN_MAX_VALUE);
		analogWrite(_redPin, redLevel);
	}

	if (_greenLevel != greenLevel) {
		_greenLevel = constrain(greenLevel, PIN_MIN_VALUE, PIN_MAX_VALUE);
		analogWrite(_greenPin, greenLevel);
	}

	if (_blueLevel != blueLevel) {
		_blueLevel = constrain(blueLevel, PIN_MIN_VALUE, PIN_MAX_VALUE);
		analogWrite(_bluePin, blueLevel);
	}

	Log.Debug("RGB: R %d\tG %d\tB %d"CR, _redLevel, _greenLevel, _blueLevel);
}

void RGBOutput::setColor(Color color) {
	switch(color) {
	case BLACK:
		setLevels(PIN_MIN_VALUE,PIN_MIN_VALUE,PIN_MIN_VALUE);
		break;
	case RED:
		setLevels(PIN_MAX_VALUE,PIN_MIN_VALUE,PIN_MIN_VALUE);
		break;
	case GREEN:
		setLevels(PIN_MIN_VALUE,PIN_MAX_VALUE,PIN_MIN_VALUE);
		break;
	case BLUE:
		setLevels(PIN_MIN_VALUE,PIN_MIN_VALUE,PIN_MAX_VALUE);
		break;
	case PURPLE:
		setLevels(PIN_MAX_VALUE,PIN_MIN_VALUE,PIN_MAX_VALUE);
		break;
	case YELLOW:
		setLevels(PIN_MAX_VALUE,PIN_MAX_VALUE,PIN_MIN_VALUE);
		break;
	case WHITE:
		setLevels(PIN_MAX_VALUE,PIN_MAX_VALUE,PIN_MAX_VALUE);
		break;
	}

}

RGBOutput::Mode RGBOutput::getMode() {
	return _currentMode;
}

void RGBOutput::setMode(Mode mode) {
	_currentMode = mode;

	if (_currentMode == NONE) {
		setLevels(0, 0, 0);
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
			spectrumValueLeft[i] = 0;
		}
		spectrumValueRight[i] = map(spectrumValueRight[i], 0, 1023, 0, 255);
		if (spectrumValueRight[i] < LBSOUND_MINVALUE) {
			spectrumValueRight[i] = 0;
		}
		digitalWrite(LBPIN_SOUND_STROBE, HIGH);
	}

	Log.Debug("RGBMusic: 0%d\t1 %d\t2 %d\t3 %d\t4 %d\t5 %d\t6 %d"CR,
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
