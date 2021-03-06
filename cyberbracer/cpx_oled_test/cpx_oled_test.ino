/*
 * This program is a technology proof of concept, working out the details of working with the OLED display 
 * over I2C and the capacitive touch sensors.  Some of this will be included in the main application, 
 * but I like to keep proof of concept work separate to verify the hardware when things don't work
 * in the main application.  Doing the proof of concept first also means I have the capabilities I need worked
 * out for the main application.
 */

#include <Adafruit_Circuit_Playground.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


//// BUTTONS
int CAP_THRESHOLD = 450;
const uint8_t BTN_UP = 0;     //readCap for A6
const uint8_t BTN_DOWN = 1;   //readCap for A7
const uint8_t BTN_SELECT = 9; //readCap for A2
const uint8_t BTN_BACK = 10;  //readCap for A3
const uint8_t BTN_USER1 = 6;  //readCap for A1
const uint8_t BTN_USER2 = 12;  //readCap for A0

//// I2C
#define OLED_I2C_ADDRESS 0x3C

//// OLED
#define SCREEN_WIDTH    128 // OLED display width, in pixels
#define SCREEN_HEIGHT   64 // OLED display height, in pixels
#define OLED_RESET      BTN_USER1 // Reset pin # (or -1 if sharing Arduino reset pin)


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//// Other
boolean DEBUG_MODE = true;

//// Functions
void debug(char* message) {
  Serial.println(message);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(message);
  display.display();
}


boolean isCapPressed(uint8_t capNum) {
  int capValue = CircuitPlayground.readCap(capNum, 30);
  if ( capValue > CAP_THRESHOLD) {
    CircuitPlayground.playTone(262, 10);
    /*
    Serial.print("Cap ");
    Serial.print(capNum);
    Serial.print(" pressed, value is ");
    Serial.println(capValue);
    */
    return true;
  }
  /*
  Serial.print("Cap ");
  Serial.print(capNum);
  Serial.print(" NOT pressed, value is ");
  Serial.println(capValue);
  */
  return false;
}

//// Main methods
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  CircuitPlayground.begin();

  Serial.println("Initializing display");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for (;;); // Don't proceed, loop forever
  }
  Serial.println("Initialized display");

  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.display();
  Serial.println("Starting");
  Serial.print("Debug is ");
  Serial.println(DEBUG_MODE);
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
