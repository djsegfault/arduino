/*
 * Sequencer.cpp
 *
 *  Created on: Dec 24, 2018
 *      Author: david
 */

#include "Sequencer.h"

Sequencer::Sequencer() {
	_enabled = 0;

}

void Sequencer::begin(RGBOutput* rgb) {
	_enabled = 0;
	_currentBank = 0;
	_currentStep = 0;
	_markStartTime = 0;
	_lastChangeTime = micros();
	_nextChangeTime = _lastChangeTime;
	_sequenceDelay = 500000L; // .5 seconds
	_rgb=rgb;
}

void Sequencer::setChannel(int bank, int step, Channel * channel) {
	_stepChannels[bank][step] = channel;
	Log.Info("[Seq][%d][%d] is channel %d"CR,
							bank,
							step,
							channel == NULL ? -1 : channel->getNumber());
}

void Sequencer::setBank(int bank) {
	// Reset before changing banks to turn off any channels currently on
	reset();
	_currentBank = bank;
	Log.Info("[Seq] Bank %d selected"CR, bank);
}

void Sequencer::on() {
	_enabled = 1;
	Log.Info("[Seq] on"CR);
	reset();
}

void Sequencer::off() {
	_enabled = 0;
	reset();
	Log.Info("[Seq] off"CR);
}

void Sequencer::toggle() {
	if(_enabled) {
		off();
	} else {
		on();
	}
}

void Sequencer::reset() {
	_markStartTime = 0;
	_lastChangeTime = micros();
	_nextChangeTime = _lastChangeTime + _sequenceDelay;
	_currentStep = 0;

	// Turn everything off
	for(int step = 0; step < LBSEQ_STEPS; step++) {
		updateChannel(step, false);
	}

	if(_rgb != NULL) {
		if(_rgb->getMode() == RGBOutput::SEQUENCE_RGB || _rgb->getMode() == RGBOutput::SEQUENCE_RANDOM) {
			_rgb->setLevels(random(LBPIN_MIN_VALUE), random(LBPIN_MIN_VALUE), random(LBPIN_MIN_VALUE));
		}
	}
}

void Sequencer::update() {
	int redLevel;
	int greenLevel;
	int blueLevel;

	if(_enabled) {
		// Mark the current time the first thing for greatest accuracy on the next sequence time.
		unsigned long currentTime = micros();
		if(currentTime >= _nextChangeTime) {
			// Time to change, move to the next step. Turn off the current channel then advance to next
			updateChannel(_currentStep, false);
			if(_currentStep == (LBSEQ_STEPS - 1)) {
				_currentStep = 0;
			} else {
				_currentStep++;
			}
			updateChannel(_currentStep, true);
			Log.Info("[Seq][%d][%d] (%d)"CR,
					_currentBank,
					_currentStep,
					_stepChannels[_currentBank][_currentStep] == NULL ? -1 : _stepChannels[_currentBank][_currentStep]->getNumber());

			_lastChangeTime = currentTime;
			_nextChangeTime = currentTime + _sequenceDelay;

			// Is RGBOutput mode SEQUENCE?
			if(_rgb != NULL) {
				if(_rgb->getMode() == RGBOutput::SEQUENCE_RGB || _rgb->getMode() == RGBOutput::SEQUENCE_RANDOM) {
					if(_rgb->getMode() == RGBOutput::SEQUENCE_RGB) {
						// @TODO Use modulo so it can handle any number of steps
						redLevel   = _currentStep == 0 ? LBPIN_MAX_VALUE : LBPIN_MIN_VALUE;
						greenLevel = _currentStep == 1 ? LBPIN_MAX_VALUE : LBPIN_MIN_VALUE;
						blueLevel  = _currentStep == 2 ? LBPIN_MAX_VALUE : LBPIN_MIN_VALUE;
					} else if(_rgb->getMode() == RGBOutput::SEQUENCE_RANDOM) {
						redLevel   = random(LBPIN_MAX_VALUE);
						greenLevel = random(LBPIN_MAX_VALUE);
						blueLevel  = random(LBPIN_MAX_VALUE);
					}
					Log.Info("[Seq]RGB [%d][%d][%d]"CR, redLevel, greenLevel, blueLevel);
					_rgb->setLevels(redLevel, greenLevel, blueLevel);
				}
			}
		}
	}

}

void Sequencer::markTime() {
	if(_markStartTime == 0) {
		// Set first mark time
		_markStartTime = micros();
		Log.Info("[Seq] Mark time start"CR);
	} else {
		// Calculate the difference and set the delay
		// Set last change time so we sequence the next update
		_sequenceDelay = micros() - _markStartTime;
		_markStartTime = 0;
		Log.Info("[Seq] Delay now %dms"CR, _sequenceDelay / 1000L);
		reset();
	}
}

void Sequencer::updateChannel(int step, bool state) {
	if(_stepChannels[_currentBank][step] != NULL) {
		if (state == true) {
			_stepChannels[_currentBank][step]->on();
		} else {
			_stepChannels[_currentBank][step]->off();
		}
	}
}

Sequencer::~Sequencer() {

}
