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


void SerialHandler::begin(LightBoard *lightBoard) {
	_lightBoard = lightBoard;
}

bool SerialHandler::checkSerial() {

	if (Serial.available() > 0) {
		// read the incoming byte:
		Serial.read();

		// say what you got:
		Serial.print("I received Serial input ");
		_lightBoard->getChannel(0)->toggle();
	}
}