/*
  SerialHandler.h - LightBrightLib - Library for controlling lights.
  Created by David Kramer.
  Released into the public domain.
  
  Handles input from PS/2 Serial
  Expects configurable declarations to be done in LightBrightConfig.h
*/
#ifndef SerialHandler_h
#define SerialHandler_h

#include "Arduino.h"
#include "LightBrightConfig.h"
#include "Channel.h"


class SerialHandler
{
	public:
		void begin(Channel *digitalChannels);
		bool handleSerial();
		bool handleKey(char key);
	protected:
		Channel *_digitalChannels;
};	

#endif