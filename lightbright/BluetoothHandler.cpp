/*
 * BluetoothHandler.cpp
 *
 *  Created on: Aug 5, 2018
 *      Author: david
 */

#include "LightBrightConfig.h"
#include "BluetoothHandler.h"

BluetoothHandler::BluetoothHandler() {
	// TODO Auto-generated constructor stub

}

BluetoothHandler::~BluetoothHandler() {
	// TODO Auto-generated destructor stub
}

void BluetoothHandler::begin() {
	LBBTH_SERIAL_PORT.begin(9600);
	Log.Info("[BT]Connecting to HC-05"CR);
	while (! LBBTH_SERIAL_PORT ) {
		Log.Info("[BT]Connecting to HC-05"CR);
		delay(1000);
	}
	Log.Info("[BT]HC-05 connected"CR);
}

char BluetoothHandler::checkBluetooth() {
	char key = 0;

	if(LBBTH_SERIAL_PORT.available() != 0) {
		key = LBBTH_SERIAL_PORT.read();
		Log.Verbose("[BT] Got key '%c'"CR , key);
	}

	return key;
}

void BluetoothHandler::sendMessage(char *message) {
	LBBTH_SERIAL_PORT.println(message);
}

