
// Third-party headers
#include <PS2Keyboard.h>


// LightBright headers
#include "LightBrightConfig.h"
#include "DigitalOutPin.h"
#include "Channel.h"
#include "KeyboardHandler.h"
#include "SerialHandler.h"

#include <Logging.h>

#define LOGLEVEL LOG_LEVEL_DEBUG

// Globals
Channel digitalChannels[LBPIN_DOUT_COUNT];
DigitalOutPin digitalPins[LBPIN_DOUT_COUNT];

DigitalOutPin *dpins;

#ifdef LBC_KEYBOARD
KeyboardHandler keyboardHandler;
#endif
SerialHandler serialHandler;

void setup() {
  Log.Init(LOGLEVEL, 9600L);
  delay(1000);
  Log.Info(CR"LightBrightMain starting"CR);

  // Initialize digital outputs
  for (int x = 0; x < LBPIN_DOUT_COUNT; x++) {
    digitalPins[x].begin(LBPIN_DOUT_START + (x * LBPIN_DOUT_INTERVAL));
    digitalChannels[x].begin(&digitalPins[x], x+1);
    Log.Info("Initialized digital channel %d to pin %d"CR, digitalChannels[x].getNumber(), digitalChannels[x].getPin()->getPinNumber());
  }

  // example code to be removed 
  dpins = digitalPins;
  int dpinm = digitalPins[3].getPinNumber();
  int dpinn = dpins[3].getPinNumber();
  

#ifdef LBC_KEYBOARD
  keyboardHandler.begin(digitalChannels);
#endif
  serialHandler.begin(digitalChannels);


}

void loop() {
  
#ifdef LBC_KEYBOARD
  keyboardHandler.handleKeyboard();
  serialHandler.handleSerial();
#endif

}



