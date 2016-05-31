/*
  KeyboardHandler - LightBrightLib - Library for controlling lights.
  Created by David Kramer.
  Released into the public domain.

  This handles keyboard input via the PS2Keyboard libarary
*/

void keyboardHandler() {

  if (keyboard.available()) {

    // read the next key
    char c = keyboard.read();
    //Log.Debug("Keyboard input: %c"CR, c);
    switch (c) {
      case 'z'  :
        DigitalChannels[0].toggle();
        break;
      case 'x'  :
        DigitalChannels[1].toggle();
        break;
      case 'c'  :
        DigitalChannels[2].toggle();
        break;
      case 'v'  :
        DigitalChannels[3].toggle();
        break;
      case 'b'  :
        DigitalChannels[4].toggle();
        break;
      case 'n'  :
        DigitalChannels[5].toggle();
        break;
      case 'm'  :
        DigitalChannels[6].toggle();
        break;
      case ','  :
        DigitalChannels[7].toggle();
        break;
    }

  }

}

