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

// RGB PWM pins
#define LBPIN_RGB_RED 4
#define LBPIN_RGB_GREEN 5
#define LBPIN_RGB_BLUE 6

////// Channels
#define LBCHANNEL_COUNT 12       // Must be LBPIN_DOUT_COUNT + LBPIN_AOUT_COUNT

// Bluetooth on Serial 2
#define LBPIN_BTH_TX 16
#define LBPIN_BTH_RX 17
#define LBPIN_BTH_KEY 32
#define LBPIN_BTH_STATE 33

// Sequencer
// How many steps in each sequence?
#define SEQ_STEPS 3
// How many different channel banks can you switch the sequencer between?
#define SEQ_BANKS 4
// RGB gets handled separately so if the bank is this then use that handling (may be larger than SEQ_BANKS)
#define SEQ_BANK_RGB 10
// the channel numbers for each step in each bank (should be  SEQ_BANKS*SEQ_STEPS values)
// Setting to negative number skips that step
#define SEQ_CHANNEL_NUMBERS { {0,1,2}, {3,5,4}, {7, 8, 9}, {0, -1, 0} }

// Other configuration settings

// Keyboard key assignments
// Each string represents a series of keys, one per channel, each one should be LBCHANNEL_COUNT long
#define LBKEY_MOMENTARY {'z','x','c','v','b','n','m',',','q','w','e','r'}
#define LBKEY_TOGGLE {'a','s','d','f','g','h','j','k','1','2','3','4'}
#define LBKEY_MASTER_MOMENTARY '/'
#define LBKEY_MASTER_TOGGLE ';'

#define LBKEY_SEQ_MARK 'o'
#define LBKEY_SEQ_TOGGLE 'p'

#define LBKEY_COMMAND_START '#'
#define LBKEY_COMMAND_END '~'

// RGB lighting configuration
#define LB_RGB_COUNT 1
#define LBRGB_RED 0
#define LBRGB_GREEN 1
#define LBRGB_BLUE 2
#define FADESPEED 5

// Sound
#define LBPIN_SOUND_RESET 30
#define LBPIN_SOUND_STROBE 31
#define LBPIN_SOUND_LEFT A14
#define LBPIN_SOUND_RIGHT A15
#define LBSOUND_MINVALUE 20

// Bluetooth on Serial 2
#define LBBTH_SERIAL_PORT Serial2

// Maximum command length
#define LB_COMMAND_MAX_LENGTH 80

#endif
