/*
 * RGBOutput.h
 *
 *  Created on: Aug 5, 2018
 *      Author: david
 */

#ifndef RGBOutput_h
#define RGBOutput_h

class RGBOutput {
public:
	RGBOutput();
	void begin(unsigned char redPin, unsigned char greenPin, unsigned char bluePin);
	void setLevels(int redLevel, int greenLevel, int blueLevel);
	void RGBCurrentState(char* loopName);
	virtual ~RGBOutput();
protected:
	unsigned char _redPin;
	unsigned char _greenPin;
	unsigned char _bluePin;
	int _redLevel;
	int _greenLevel;
	int _blueLevel;
};

#endif /* RGBOUTPUT_H_ */
