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
#define LBPIN_KBD_DATA 22
#define LBPIN_KBD_IRQ 3

// Digital outputs
#define LBPIN_DOUT_START 22         // First pin
#define LBPIN_DOUT_INTERVAL 2   // 1 for every pin, 2 for every other pin (
                                // eg where odd pins are in one row and even pins are in the other)
#define LBPIN_DOUT_COUNT 8      // How many digital outputs are there?                                

// Other configuration settings

// How many digital




#endif
