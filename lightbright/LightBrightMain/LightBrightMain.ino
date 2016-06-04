

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
Channel DigitalChannels[LBPIN_DOUT_COUNT];
DigitalOutPin DigitalPins[LBPIN_DOUT_COUNT];

#ifdef LBC_KEYBOARD
PS2Keyboard keyboard;
#endif

void setup() {
  Log.Init(LOGLEVEL, 9600L);
  delay(500);
  Log.Info(CR"LightBrightMain starting"CR);

  // Initialize digital outputs
  for (int x = 0; x < LBPIN_DOUT_COUNT; x++) {
    DigitalPins[x].setPinNumber(LBPIN_DOUT_START + (x * LBPIN_DOUT_INTERVAL));
    DigitalChannels[x].setPin(DigitalPins[x]);
    DigitalChannels[x].setNumber(x+1);
    Log.Info("Initialized digital channel %d to pin %d"CR, DigitalChannels[x].getNumber(), DigitalChannels[x].getPin().getPinNumber());
  }


#ifdef LBC_KEYBOARD
  keyboard.begin(LBPIN_KBD_DATA, LBPIN_KBD_IRQ);
#endif
}

void loop() {
  
#ifdef LBC_KEYBOARD
  keyboardHandler();
#endif

}



