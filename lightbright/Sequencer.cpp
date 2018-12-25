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

void Sequencer::begin(Channel *stepChannels) {
	_enabled = 0;
	_markStartTime = 0;
	_lastChangeTime = micros();
	_nextChangeTime = _lastChangeTime;
	_sequenceDelay = 500000L; // .5 seconds
	_stepChannels = stepChannels;
}

void Sequencer::on() {
	_enabled = 1;
	Log.Info("[Seq] on"CR);
	reset();
}

void Sequencer::off() {
	_enabled = 0;
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
	_lastChangeTime = micros();
	_nextChangeTime = _lastChangeTime + _sequenceDelay;
	_currentStep = 0;
	updateChannels();
}

void Sequencer::update() {
	if(_enabled) {
		unsigned long currentTime = micros();
		if(currentTime >= _nextChangeTime) {
			// Time to change, move to the next step
			if(_currentStep == (SEQ_STEPS - 1)) {
				_currentStep = 0;
			} else {
				_currentStep++;
			}
			updateChannels();
			_lastChangeTime = currentTime;
			_nextChangeTime = currentTime + _sequenceDelay;
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

void Sequencer::updateChannels() {
	Log.Info("[Seq] step=%d"CR, _currentStep);
	for (int step = 0; step < SEQ_STEPS; step++) {
		if (step == _currentStep) {
			_stepChannels[step].on();
		} else {
			_stepChannels[step].off();
		}
	}

	// Is RGBOutput mode SEQUENCE?
}

Sequencer::~Sequencer() {

}
