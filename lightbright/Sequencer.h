/*
 * Sequencer.h
 *
 *  Created on: Dec 24, 2018
 *      Author: david
 */

#ifndef LIGHTBRIGHT_SEQUENCER_H_
#define LIGHTBRIGHT_SEQUENCER_H_

#include "Arduino.h"
#include <Logging.h>
#include "LightBrightConfig.h"
#include "LightBoard.h"
#include "Channel.h"
#include "RGBOutput.h"


class Sequencer {
public:
	Sequencer();
	void begin(RGBOutput* rgb);
	void setChannel(int bank, int step, Channel * channel);
	Channel* getChannel(int bank, int step);
	void setBank(int bank);
	void on();
	void off();
	void toggle();
	void reset();
	void markTime();
	void update();
	virtual ~Sequencer();
protected:
	int _enabled;
	// zero-based
	int _currentBank;
	int _currentStep;
	Channel *_stepChannels[LBSEQ_BANKS][LBSEQ_STEPS];
	// Times are in microseconds
	unsigned long _markStartTime;
	unsigned long _lastChangeTime;
	unsigned long _nextChangeTime;
	unsigned long _sequenceDelay;
	RGBOutput* _rgb;
	void updateChannel(int step, bool state);
};

#endif /* LIGHTBRIGHT_SEQUENCER_H_ */
