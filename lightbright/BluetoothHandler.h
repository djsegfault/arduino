/*
 * BluetoothHandler.h
 *
 *  Created on: Aug 5, 2018
 *      Author: david
 */

#ifndef BluetoothHandler_h_
#define BluetoothHandler_h_

#include "Arduino.h"
#include <Logging.h>

class BluetoothHandler {
public:
	BluetoothHandler();
	void begin();
	char checkBluetooth();
	void sendMessage(char *message);
	virtual ~BluetoothHandler();

protected:
};

#endif /* BluetoothHandler_h_ */
