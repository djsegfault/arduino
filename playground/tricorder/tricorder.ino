#include <Adafruit_CircuitPlayground.h>

#include "tricorder.h"
#include "infrared_codes_phone.h"
#include "flashlightMode.h"
#include "colorCycleMode.h"
#include "nothingMode.h"
#include "sparkleMode.h"


// Mode changing:  All of these are parallel arrays
// Array of setup functions for each mode
static void (*modeSetups[])(void) = {nothingSetup, colorCycleSetup, flashlightSetup, sparkleSetup};
static void (*modeLoops[])(void) = {nothingLoop, colorCycleLoop, flashlightLoop, sparkleLoop};
static int capSwitchModes[] = { CAP_SWITCH_A4, CAP_SWITCH_A5, CAP_SWITCH_A6, CAP_SWITCH_A7 };

void setup() {
  // Initialize serial port and circuit playground library.
  Serial.begin(115200);
  Serial.println("Circuit Playground Tricorder: David Kramer");
  CircuitPlayground.begin();

  CircuitPlayground.irReceiver.enableIRIn(); // Start the receiver

  // Mode setup
  current_mode = MODE_COLORCYCLE;
  current_brightness = LED_DEFAULT_BRIGHTNESS;
  current_speed = SPEED_DEFAULT;
  ir_protocol = 0;
  ir_value = 0;
}

void changeMode(int new_mode) {
  if (current_mode != new_mode) {
    Serial.print("New mode is ");
    Serial.println(new_mode);
    Serial.print("Current brightness is ");
    Serial.println(current_brightness);
    Serial.print("Current speed is ");
    Serial.println(current_speed);
    current_mode = new_mode;
    CircuitPlayground.setBrightness(current_brightness);
    modeSetups[current_mode]();
  }
}

/*
  void infraredLoop() {
  if (CircuitPlayground.irReceiver.getResults()) {
    Serial.println("IR R");
    //attempt to decode it
    if (CircuitPlayground.irDecoder.decode()) {
      ir_value = CircuitPlayground.irDecoder.value;
      ir_bits = CircuitPlayground.irDecoder.bits;
      CircuitPlayground.irDecoder.dumpResults(true);
      Serial.print("value=[");
      Serial.print(ir_value);
      Serial.print("]  bits=[");
      Serial.print(ir_bits);
      Serial.println("]");

      if (ir_value == IR_MODE_NOTHING) {
        changeMode(MODE_NOTHING);
      } else if (ir_value == IR_MODE_COLORCYCLE) {
        changeMode(MODE_COLORCYCLE);
      } else if (ir_value == IR_MODE_FLASHLIGHT) {
        changeMode(MODE_FLASHLIGHT);
      }
    }
    CircuitPlayground.irReceiver.enableIRIn();      //Restart receiver
  }
  }
*/


int capSwitchPressed(int switchNumber) {
  int isPressed = 0;
  if (CircuitPlayground.readCap(switchNumber, CAP_SAMPLES) >= CAP_THRESHOLD) {
    Serial.print(switchNumber);
    Serial.println(" is pressed");
    isPressed = 1;
  } else {
    //Serial.print(switchNumber);
    //erial.println(" is NOT pressed");
  }

  return isPressed;
}


void controlsLoop() {
  capSwitchPressed(CAP_SWITCH_A1);
  capSwitchPressed(CAP_SWITCH_A2);
  capSwitchPressed(CAP_SWITCH_A3);
  capSwitchPressed(CAP_SWITCH_A4);
  capSwitchPressed(CAP_SWITCH_A5);
  capSwitchPressed(CAP_SWITCH_A6);
  capSwitchPressed(CAP_SWITCH_A7);

  for (int mode = 0; mode <= MAX_MODE; mode++) {
    if (mode != current_mode) {
      if (CircuitPlayground.readCap(capSwitchModes[mode], CAP_SAMPLES) >= CAP_THRESHOLD) {
        changeMode(mode);
      }
    }
  }

  // Dimmer
  if (CircuitPlayground.readCap(CAP_SWITCH_A2, CAP_SAMPLES) >= CAP_THRESHOLD
      && current_brightness > (LED_MIN_BRIGHTNESS + LED_DELTA_BRIGHTNESS)) {
    current_brightness -= LED_DELTA_BRIGHTNESS;
    Serial.print("Brightness now ");
    Serial.println(current_brightness);
    CircuitPlayground.setBrightness(current_brightness);
  }

  // Brighter
  if (CircuitPlayground.readCap(CAP_SWITCH_A3, CAP_SAMPLES) >= CAP_THRESHOLD
      && current_brightness < (LED_MAX_BRIGHTNESS - LED_DELTA_BRIGHTNESS)) {
    current_brightness += LED_DELTA_BRIGHTNESS;
    Serial.print("Brightness now ");
    Serial.println(current_brightness);
    CircuitPlayground.setBrightness(current_brightness);
  }

  // Faster
  if (CircuitPlayground.leftButton()) {
    if (current_speed > (SPEED_MIN + SPEED_DELTA)) {
      current_speed -= SPEED_DELTA;
      Serial.print("Speed now ");
      Serial.println(current_speed);
    } else {
      Serial.print("Speed not increased from ");
      Serial.println(current_speed);
    }
  }

  // Slower
  if (CircuitPlayground.rightButton() ) {
    if (current_speed < (SPEED_MAX - SPEED_DELTA)) {
      current_speed += SPEED_DELTA;
      Serial.print("Speed now ");
      Serial.println(current_speed);
    } else
      Serial.print("Speed not decreased from ");
      Serial.println(current_speed);
    }
  }


void loop() {
  //infraredLoop();
  controlsLoop();
  modeLoops[current_mode]();

}

