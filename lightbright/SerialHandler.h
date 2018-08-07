/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright
  
  Serialhandler.h
  Handles serial communications
  NOTE This is a stub implementation, 
  Eventually I will have a command processor and DSM this will call
*/

#ifndef SerialHandler_h
#define SerialHandler_h

#include "Arduino.h"
#include "LightBrightConfig.h"
#include "LightBoard.h"
#include "Channel.h"


class SerialHandler
{
	public:
		void begin(LightBoard *lightBoard);
		bool checkSerial();
		bool handleKey(char key);
	protected:
		LightBoard *_lightBoard;
};	

#endif