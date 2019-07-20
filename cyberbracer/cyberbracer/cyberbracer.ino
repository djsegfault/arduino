/*
 * This software is the driver for my "cyberbracer" cosplay. 
 * See https://github.com/djsegfault/arduino/tree/master/cyberbracer for source and project information
 * 
 * Copyright 2019 David Kramer david@thekramers.net
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

////-------------------------------------------------------------------- Includes
#include <Adafruit_Circuit_Playground.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MenuSystem.h>
#include "OLEDMenuRenderer.h"

////-------------------------------------------------------------------- Globals
//// BUTTONS
int CAP_THRESHOLD=450;          //May change, but global. Used for capacitive touch sensitivity
const uint8_t BTN_UP=0;         //readCap for A6
const uint8_t BTN_DOWN=1;       //readCap for A7
const uint8_t BTN_SELECT=9;     //readCap for A2
const uint8_t BTN_BACK=10;      //readCap for A3
const uint8_t BTN_USER1=6;      //readCap for A1
const uint8_t BTN_USER2=12;     //readCap for A0

//// I2C
const uint8_t OLED_I2C_ADDRESS=0x3C;

//// OLED
const int SCREEN_WIDTH=128;     // OLED display width, in pixels
const int SCREEN_HEIGHT=64;     // OLED display height, in pixels
// -1 did not work for me, but 6 does (A1) because the signal for OLED reset looks so different from CapTouch
const uint8_t OLED_RESET=6;     // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//// MenuSystem
OLEDMenuRenderer menuRenderer(oled, SCREEN_WIDTH, SCREEN_HEIGHT);
MenuSystem menuSystem(menuRenderer);

//// Operations
boolean DEBUG_MODE = true;

////-------------------------------------------------------------------- Functions
boolean isCapPressed(uint8_t capNum) {
  int capValue = CircuitPlayground.readCap(capNum, 30);
  if ( capValue > CAP_THRESHOLD) {
    CircuitPlayground.playTone(262, 10);
    if(DEBUG_MODE == true) {
      Serial.print("Cap ");
      Serial.print(capNum);
      Serial.print(" pressed, value is ");
      Serial.println(capValue);
    }
    return true;
  }

  return false;
}

void debug(char* message) {
  if(DEBUG_MODE == true) {
    Serial.println(message);
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.println(message);
    oled.display();
  }
}



////-------------------------------------------------------------------- Main
void setup() {

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  CircuitPlayground.begin();

  Serial.println("Starting");
  // SSD1306_SWITCHCAPVCC = generate oled voltage from 3.3V internally
  if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for (;;); // Don't proceed, loop forever
  }
  Serial.println("Initialized oled");
  

  // Clear the buffer
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.display();
  Serial.println("Starting");
  Serial.print("Debug is ");
  Serial.println(DEBUG_MODE);
}

void deleteme() {
  int a=1;
}

void loop() {
  //Serial.println("Top of loop");
  if (CircuitPlayground.rightButton()) {
    debug("Right");
  }

  if (CircuitPlayground.leftButton()) {
    debug("Left");
  }

  if (isCapPressed(BTN_UP)) {
    debug("Up");
  }
  if (isCapPressed(BTN_DOWN)) {
    debug("Down");
  }
  if (isCapPressed(BTN_SELECT)) {
    debug("Select");
  }
  if (isCapPressed(BTN_BACK)) {
    debug("Back");
  }
  if (isCapPressed(BTN_USER1)) {
    debug("User 1");
  }
  /*
  if (isCapPressed(BTN_USER2)) {
    debug("User 2");
  }
  */

  digitalWrite(LED_BUILTIN, 1);
  delay(200);
  digitalWrite(LED_BUILTIN, 0);
}
