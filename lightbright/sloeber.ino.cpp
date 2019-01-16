#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2018-12-23 18:05:16

#include "Arduino.h"
#include <PS2Keyboard.h>
#include "LightBrightConfig.h"
#include "DigitalOutPin.h"
#include "AnalogOutPin.h"
#include "Channel.h"
#include "KeyboardHandler.h"
#include "BluetoothHandler.h"
#include "SerialHandler.h"
#include "RGBOutput.h"
#include "LightBoard.h"
#include <Logging.h>

void setup() ;
void loop() ;

void checkCommandTimeout();
void clearCommandBuffer();
void handleKey(char key) ;
void handleCommand() ;
void handleBluetoothCommand();
void handleMasterCommand();
void handleRGBCommand();
void handleSequenceCommand();
void handleTextCommand();

void clearMomentaryKey(int x) ;
int memoryAvailable();

#include "LightBrightMain.ino"

#endif
