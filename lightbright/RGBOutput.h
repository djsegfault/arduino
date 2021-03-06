/*
 * RGBOutput.h
 *
 *  Created on: Aug 5, 2018
 *      Author: david
 */

#ifndef RGBOutput_h
#define RGBOutput_h

#include "Arduino.h"
#include "LightBrightConfig.h"
#include "Channel.h"

class RGBOutput {
public:
	RGBOutput();
	enum Mode {
		NONE, MUSIC, FADE, SEQUENCE_RGB, SEQUENCE_RANDOM
	};
	enum Color {
		BLACK, RED, GREEN, BLUE, PURPLE, YELLOW, WHITE
	};
	void begin(unsigned char redPin, unsigned char greenPin, unsigned char bluePin, Channel *masterChannel);
	void setLevels(int redLevel, int greenLevel, int blueLevel);
	void setColor(Color color);
	void RGBCurrentState(char* loopName);
	RGBOutput::Mode getMode();
	void setMode(Mode mode);
	void update();
	virtual ~RGBOutput();
protected:
	unsigned char _redPin;
	unsigned char _greenPin;
	unsigned char _bluePin;
	Channel *_masterChannel;
	int _redLevel;
	int _greenLevel;
	int _blueLevel;
	int spectrumValueLeft[7];
	int spectrumValueRight[7];
	Mode _currentMode;
	void updateMusic();
};

#endif /* RGBOUTPUT_H_ */
