// Modes
#define MODE_NOTHING 0
#define MODE_COLORCYCLE 1
#define MODE_FLASHLIGHT 2
#define MAX_MODE 2

// Speeds (smaller is faster)
// TODO: Refactor as 1 to 10 and scale where needed
#define SPEED_DEFAULT 20
#define SPEED_MAX 200
#define SPEED_MIN 1
#define SPEED_DELTA 1


// Switches
#define CAP_THRESHOLD    300  // Threshold for a capacitive touch (higher = less sensitive).
#define CAP_SAMPLES      20   // Number of samples to take for a capacitive touch read.
// See https://cdn-learn.adafruit.com/assets/assets/000/047/156/large1024/circuit_playground_Adafruit_Circuit_Playground_Express_Pinout.png?1507829017
#define CAP_SWITCH_A7    1
#define CAP_SWITCH_A6    0
#define CAP_SWITCH_A5    2
#define CAP_SWITCH_A4    3
#define CAP_SWITCH_A3    10
#define CAP_SWITCH_A2    9
#define CAP_SWITCH_A1    6

// LEDS  RENAME BRIGHTNESS_MIN....
#define LED_DEFAULT_BRIGHTNESS 30
#define LED_MIN_BRIGHTNESS 0
#define LED_MAX_BRIGHTNESS 255
#define LED_DELTA_BRIGHTNESS 5


// Globals
int current_mode;
int current_brightness;
int current_speed;

uint8_t ir_protocol; //  Indicates we've not received a code yet
uint32_t ir_value;
uint16_t ir_bits;


