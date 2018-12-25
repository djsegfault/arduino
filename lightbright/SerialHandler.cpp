/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright
  
  Serialhandler.cpp
  Handles serial communications
  NOTE This is a stub implementation, 
  Eventually I will have a command processor and DSM this will call
*/

#include "SerialHandler.h"


void SerialHandler::begin() {
}

char SerialHandler::checkSerial() {

	if (Serial.available() > 0) {
		return Serial.read();
	}
	return 0;
}
