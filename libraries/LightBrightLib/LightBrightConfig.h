/*
  LightBrightConfig.h - LightBrightLib - Library for controlling lights.
  Created by David Kramer.
  Released into the public domain.

  This is a collection of configuration variables and constants that
  you may want to change specific to your usage of the library.  It
  has pin assignments, feature switches, etc.
*/

#ifndef LightBrightConfig_h
#define LightBrightConfig_h

////// Feature switches.  Uncomment to enable the feature.
#define LBC_KEYBOARD YES

////// Pin assignments
// Keyboard
#define LBPIN_KBD_DATA 53
#define LBPIN_KBD_IRQ 3

// Digital outputs
#define LBPIN_DOUT_START 22         // First pin
#define LBPIN_DOUT_INTERVAL 2   // 1 for every pin, 2 for every other pin (
                                // eg where odd pins are in one row and even pins are in the other)
#define LBPIN_DOUT_COUNT 8      // How many digital outputs are there?                                

// Other configuration settings

// Keyboard key assignments
// Each string represents a series of keys, one per channel, each one should be as long as the number of channels of that kind.
#define LBKEY_DOUT_MOMENTARY {'z','x','c','v','b','n','m',','}
#define LBKEY_DOUT_TOGGLE {'a','s','d','f','g','h','j','k'}
#define LBKEY_MASTER_MOMENTARY '.'
#define LBKEY_MASTER_TOGGLE 'l'





#endif
