#include "Arduino.h"
#include "Logging.h"

#include "SerialHandler.h"


void SerialHandler::begin(LightBoard *lightBoard) {
	_lightBoard = lightBoard;
	pinMode(13, OUTPUT);

}

bool SerialHandler::handleSerial() {

	if (Serial.available() > 0) {
		// read the incoming byte:
		Serial.read();

		// say what you got:
		Serial.print("I received Serial input ");
		_lightBoard->getDigitalChannel(0)->toggle();
	}
}