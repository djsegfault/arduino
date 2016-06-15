

// Third-party headers
#include <PS2Keyboard.h>


// LightBright headers
#include "LightBrightConfig.h"
#include "DigitalOutPin.h"
#include "Channel.h"
#include "KeyboardHandler.h"

#include <Logging.h>

#define LOGLEVEL LOG_LEVEL_VERBOSE

// Globals
Channel digitalChannels[LBPIN_DOUT_COUNT];
DigitalOutPin digitalPins[LBPIN_DOUT_COUNT];

#ifdef LBC_KEYBOARD
KeyboardHandler keyboardHandler;
#endif

void setup() {
  Log.Init(LOGLEVEL, 9600L);
  delay(500);
  Log.Info(CR"LightBrightMain starting"CR);

  // Initialize digital outputs
  for (int x = 0; x < LBPIN_DOUT_COUNT; x++) {
    digitalPins[x].setPinNumber(LBPIN_DOUT_START + (x * LBPIN_DOUT_INTERVAL));
    digitalChannels[x].setPin(digitalPins[x]);
    digitalChannels[x].setNumber(x+1);
    Log.Info("Initialized digital channel %d to pin %d"CR, digitalChannels[x].getNumber(), digitalChannels[x].getPin().getPinNumber());
  }

#ifdef LBC_KEYBOARD
  keyboardHandler.begin(digitalChannels);
#endif
}

void loop() {
  
#ifdef LBC_KEYBOARD
  keyboardHandler.handleKeyboard();
#endif

}



