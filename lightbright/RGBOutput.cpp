/*
 * RGBOutput.cpp
 *
 *  Created on: Aug 5, 2018
 *      Author: david
 */

#include "Arduino.h"
#include "Logging.h"
#include "RGBOutput.h"

RGBOutput::RGBOutput() {
	_redPin = 0;
	_greenPin = 0;
	_bluePin = 0;
	_redLevel = 0;
	_greenLevel = 0;
	_blueLevel = 0;
}

RGBOutput::~RGBOutput() {
	// TODO Auto-generated destructor stub
}

void RGBOutput::begin(unsigned char redPin, unsigned char greenPin, unsigned char bluePin) {
	_redPin = redPin;
	_greenPin = greenPin;
	_bluePin = bluePin;

	pinMode(_redPin, OUTPUT);
	pinMode(_greenPin, OUTPUT);
	pinMode(_bluePin, OUTPUT);

	analogWrite(_redPin, 0);
	analogWrite(_greenPin, 0);
	analogWrite(_bluePin, 0);
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
		_redLevel = constrain(redLevel,0,255);
		analogWrite(_redPin, redLevel);
	}

	if (_greenLevel != greenLevel) {
		_greenLevel = constrain(greenLevel,0,255);
		analogWrite(_greenPin, greenLevel);
	}

	if (_blueLevel != blueLevel) {
		_blueLevel = constrain(blueLevel,0,255);
		analogWrite(_bluePin, blueLevel);
	}
}
