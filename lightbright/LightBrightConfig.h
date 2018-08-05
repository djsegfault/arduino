/*
  MIT License   Copyright (c) 2016 David Kramer
  LightBrightLib - Library for controlling lights.
  https://github.com/djsegfault/arduino/wiki/Project-LightBright

  LightBrightConfig.h
  This is a collection of configuration variables and constants that
  you may want to change specific to your usage of the library.  It
  has pin assignments, feature switches, etc.
*/

#ifndef LightBrightConfig_h
#define LightBrightConfig_h

////// Current debugging level
#define LOGLEVEL LOG_LEVEL_VERBOSE

////// Feature switches.  Uncomment to enable the feature.
#define LBC_KEYBOARD YES

////// Pin assignments
// Keyboard
#define LBPIN_KBD_DATA 53
#define LBPIN_KBD_IRQ 3

// Master pin (should be a digital output
#define LBPIN_DOUT_MASTER 13    // Use 13 so on-board light indicates master

// Digital outputs
#define LBPIN_DOUT_START 22     // First pin
#define LBPIN_DOUT_INTERVAL 1   // 1 for every pin, 2 for every other pin (because the Mega has side by side pins)
                                // eg where odd pins are in one row and even pins are in the other)
#define LBPIN_DOUT_COUNT 8      // How many digital outputs are there?  

// Analog (PWM) outputs
#define LBPIN_AOUT_START 4       // First pin
#define LBPIN_AOUT_INTERVAL 1    // 1 for every pin, 2 for every other pin (Should always be 1)
#define LBPIN_AOUT_COUNT 4       // How many analog outputs are there?

////// Channels
#define LBCHANNEL_COUNT 12       // Must be LBPIN_DOUT_COUNT + LBPIN_AOUT_COUNT


// Other configuration settings

// Keyboard key assignments
// Each string represents a series of keys, one per channel, each one should be LBCHANNEL_COUNT long
#define LBKEY_MOMENTARY {'z','x','c','v','b','n','m',',','q','w','e','r'}
#define LBKEY_TOGGLE {'a','s','d','f','g','h','j','k','1','2','3','4'}
#define LBKEY_MASTER_MOMENTARY '/'
#define LBKEY_MASTER_TOGGLE ';'



#endif