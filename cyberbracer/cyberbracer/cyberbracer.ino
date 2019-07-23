/*
   This software is the driver for my "cyberbracer" cosplay.
   See https://github.com/djsegfault/arduino/tree/master/cyberbracer for source and project information

   Copyright 2019 David Kramer david@thekramers.net

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

////-------------------------------------------------------------------- Includes
#include <Adafruit_Circuit_Playground.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MenuSystem.h>

////-------------------------------------------------------------------- Globals
//// BUTTONS
int CAP_THRESHOLD = 450;        //May change, but global. Used for capacitive touch sensitivity
const uint8_t BTN_UP = 0;       //readCap for A6
const uint8_t BTN_DOWN = 1;     //readCap for A7
const uint8_t BTN_SELECT = 9;   //readCap for A2
const uint8_t BTN_BACK = 10;    //readCap for A3
const uint8_t BTN_USER1 = 6;    //readCap for A1
const uint8_t BTN_USER2 = 12;   //readCap for A0

//// I2C
const uint8_t OLED_I2C_ADDRESS = 0x3C;

//// OLED
const int SCREEN_WIDTH = 128;   // OLED display width, in pixels
const int SCREEN_HEIGHT = 64;   // OLED display height, in pixels
// -1 did not work for me, but 6 does (A1) because the signal for OLED reset looks so different from CapTouch
const uint8_t OLED_RESET = 6;   // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//// Operations
boolean DEBUG_MODE = true;

char messageBuffer[200];



////-------------------------------------------------------------------- General functions
boolean isCapPressed(uint8_t capNum) {
  int capValue = CircuitPlayground.readCap(capNum, 30);
  if ( capValue > CAP_THRESHOLD) {
    CircuitPlayground.playTone(262, 10);
    if (DEBUG_MODE == true) {
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
  if (DEBUG_MODE == true) {
    Serial.println(message);
    /*
      oled.clearDisplay();
      oled.setCursor(0, 0);
      oled.println(message);
      oled.display();
    */
  }
}



////-------------------------------------------------------------------- Animations
// TO DO make virtual?
class Activity {
  protected:
    unsigned long currTime = 0;      // Current time in millis, updated every call to update()
    unsigned long lastUpdateTime = 0; // Last time the update ran
    unsigned long interval = 0;      // How many millis between updates
    char* name;                      // Name of the activity
  public:
    Activity(char* name, unsigned long interval) {
      this->name = name;
      this->interval = interval;
    }

    virtual void update() {
    }

    char* getName() {
      return name;
    }

    boolean isTimeToUpdate() {
      currTime = millis();
      sprintf(messageBuffer, "Update? %lu %lu %lu", currTime, lastUpdateTime, interval);
      Serial.println(messageBuffer);
      if ((lastUpdateTime == 0) || (currTime - lastUpdateTime > interval) ) {
        lastUpdateTime = currTime;
        return true;
      } else {
        return false;
      }
    }

};

class NullActivity : public Activity {
  private:
  public:
  NullActivity() : Activity("NullActivity", 1000) {
    }
    
    void update() {
      Activity::update();
      debug("NulllActivity updates");
    }
};

class BlinkActivity : public Activity {
  private:
    boolean isLightOn = false;
  public:
    BlinkActivity() : Activity("BlinkActivity", 2000) {
    }
    
    void update() {
      debug("LightActivity updating?");
      if (isTimeToUpdate()) {
        debug("LightActivity updating");
        if (isLightOn == true) {
          isLightOn = false;
          digitalWrite(LED_BUILTIN, 0);
        } else {
          isLightOn = true;
          digitalWrite(LED_BUILTIN, 1);
        }

        lastUpdateTime = millis();
      }
    }
};

// The singletons for each activity
NullActivity nullActivity;
BlinkActivity blinkActivity;


////-------------------------------------------------------------------- MenuSystem

// This is the current activity as updated from the menus
Activity *currentActivity;

//// Rendering classes
class MyRenderer : public MenuComponentRenderer {
  public:
    void render(Menu const& menu) const {
      oled.clearDisplay();
      oled.setCursor(0, 0);
      Serial.print("Displaying menu");
      Serial.println(menu.get_name());

      if (menu.get_name() == "") {
        oled.println("Main Menu");
      } else {
        oled.println(menu.get_name());
      }

      for (int i = 0; i < menu.get_num_components(); ++i) {
        MenuComponent const* cp_m_comp = menu.get_menu_component(i);
        if (cp_m_comp->is_current()) {
          oled.print(">");
        } else {
          oled.print(" ");
        }
        cp_m_comp->render(*this);

        oled.println("");
      }
      Serial.println("Displaying menu");
      oled.display();
    }

    void render_menu_item(MenuItem const& menu_item) const {
      Serial.print("Rendering menu item ");
      Serial.println(menu_item.get_name());
      oled.print(menu_item.get_name());
    }

    void render_back_menu_item(BackMenuItem const& menu_item) const {
      oled.print(menu_item.get_name());
    }

    void render_numeric_menu_item(NumericMenuItem const& menu_item) const {
      Serial.print("Rendering menu item");
      Serial.println(menu_item.get_name());
      oled.print(menu_item.get_name());
    }

    void render_menu(Menu const& menu) const {
      oled.print(menu.get_name());
    }
};

//// Menu items
MyRenderer menuRenderer;
MenuSystem menuSystem(menuRenderer);

Menu mmSensorsMenu("Sensors");
MenuItem sensorLight("Light", &mainMenuHandler);
MenuItem sensorSound("Sound", &mainMenuHandler);

Menu mmAnimMenu("Animations");
MenuItem animDemo("Demo", &mainMenuHandler);
MenuItem animLight("Flashlight", &mainMenuHandler);

Menu mmSetupMenu("Setup", &mainMenuHandler);
MenuItem setupSenseUp("CapSense Up", &mainMenuHandler);
MenuItem setupSenseDown("CapSense Down", &mainMenuHandler);
MenuItem setupDebugOn("Debug On", &mainMenuHandler);
MenuItem setupDebugOff("Debug Off", &mainMenuHandler);


//// menu selection handlers
void mainMenuHandler(MenuComponent* p_menu_component) {
  Serial.print("[");
  Serial.print(p_menu_component->get_name());
  Serial.println("] selected");

  if (strcmp(p_menu_component->get_name(), "Light") == 0) {
    Serial.println("Setting to Light");
    currentActivity = &blinkActivity;
  } else if (strcmp(p_menu_component->get_name(), "Sound") == 0) {
    Serial.println("Setting to Null");
    currentActivity = &nullActivity;
  } else {
    Serial.println("UNKNOWN ACTIVITY");
  }

  sprintf(messageBuffer, "nullActivity is %p  blinkActivity '%s' is %p current is %p",
          &nullActivity,
          blinkActivity.getName(),
          &blinkActivity,
          currentActivity);
  Serial.println(messageBuffer);

  Serial.print(" Blink activity is ");
  Serial.println(blinkActivity.getName());


  Serial.print(" Current activity is ");
  Serial.println(currentActivity->getName());

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


  // Build the menus
  menuSystem.get_root_menu().add_menu(&mmSensorsMenu);
  menuSystem.get_root_menu().add_menu(&mmAnimMenu);
  menuSystem.get_root_menu().add_menu(&mmSetupMenu);

  mmSensorsMenu.add_item(&sensorLight);
  mmSensorsMenu.add_item(&sensorSound);

  mmAnimMenu.add_item(&animDemo);
  mmAnimMenu.add_item(&animLight);

  mmSetupMenu.add_item(&setupSenseUp);
  mmSetupMenu.add_item(&setupSenseDown);
  mmSetupMenu.add_item(&setupDebugOn);
  mmSetupMenu.add_item(&setupDebugOff);

  currentActivity = &blinkActivity;

  Serial.println("Starting");
  //Serial.print("Debug is ");
  //Serial.println(DEBUG_MODE);
  delay(1000);
  Serial.println("Starting 1");
  delay(1000);
  Serial.println("Starting 2");
  delay(1000);
  Serial.println("Starting 3");
  delay(1000);


  // Clear the buffer
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.println("OLED is working!!");
  oled.display();
  Serial.println("OLED should be working");
  delay(5000);


  menuSystem.display();
  Serial.println("Menu should be displayed");

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
    menuSystem.prev();
    menuSystem.display();
  }
  if (isCapPressed(BTN_DOWN)) {
    debug("Down");
    menuSystem.next();
    menuSystem.display();
  }
  if (isCapPressed(BTN_SELECT)) {
    debug("Select");
    menuSystem.select();
    delay(2000);
    menuSystem.display();
  }
  if (isCapPressed(BTN_BACK)) {
    debug("Back");
    menuSystem.back();
    menuSystem.display();
  }
  if (isCapPressed(BTN_USER1)) {
    debug("User 1");
  }
  /*
    if (isCapPressed(BTN_USER2)) {
    debug("User 2");
    }
  */

  currentActivity->getName();
  currentActivity->update();

  /*
    digitalWrite(LED_BUILTIN, 1);
    delay(200);
    digitalWrite(LED_BUILTIN, 0);
  */
}
