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
	while (! LBBTH_SERIAL_PORT ) {
		Log.Info("Bluetooth Waiting for connection to module"CR);
		delay(1000);
	}
	Log.Info("Bluetooth module connected"CR);
}

char BluetoothHandler::checkBluetooth() {
	char key = 0;

	if(LBBTH_SERIAL_PORT.available() != 0) {
		key = LBBTH_SERIAL_PORT.read();
		Log.Debug("Bluetooth: got key '%c'"CR , key);
	}

	return key;
}

void BluetoothHandler::sendMessage(char *message) {
	LBBTH_SERIAL_PORT.println(message);
}

