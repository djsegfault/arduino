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

////-------------------------------------------------------------------- Utility functions
void resetDisplay() {
  digitalWrite(LED_BUILTIN, 0);
  CircuitPlayground.clearPixels();
}


// Returns the next pixel to start with for the next iteration
uint8_t colorWheel(uint8_t startPixel) {
  uint8_t currPixel = startPixel;
  uint8_t nextPixel;
  CircuitPlayground.clearPixels();

  for (int x = 0; x <= 9; x++) {
    Serial.println(messageBuffer);
    CircuitPlayground.setPixelColor(currPixel, CircuitPlayground.colorWheel(25 * x));

    if (currPixel == 9) {
      currPixel = 0;
    } else {
      currPixel++;
    }
  }

  if (startPixel == 9) {
    currPixel = 0;
  } else {
    currPixel = startPixel + 1;
  }

  return currPixel;
}

////-------------------------------------------------------------------- Base Activity
Activity::Activity(char* name, unsigned long interval) {
  this->name = name;
  this->interval = interval;
}

void Activity::update() {
}

char* Activity::getName() {
  return name;
}

boolean Activity::isTimeToUpdate() {
  currTime = millis();
  /*
    // For debugging activity updates, should not be in normal debugging
    sprintf(messageBuffer, "Update? curMilli=%lu lastMilli=%lu intervial%lu", currTime, lastUpdateTime, interval);
    Serial.println(messageBuffer);
  */

  // If this is the first time, run the update to start the cycle
  // If an Activity doesn't want to do updates, set interval to 0

  if ( (interval > 0) && (lastUpdateTime == 0 || currTime - lastUpdateTime > interval) ) {
    lastUpdateTime = currTime;
    return true;
  } else {
    return false;
  }
}

void Activity::updated() {
  lastUpdateTime = currTime;
}


////-------------------------------------------------------------------- NullActivity
NullActivity::NullActivity() : Activity("NullActivity", 10000) {
}

void NullActivity::update() {
  resetDisplay();
  Serial.println("NulllActivity updates");
}

void NullActivity::leftButtonPressed() {
}
void NullActivity::rightButtonPressed() {
}


////-------------------------------------------------------------------- BlinkActivity
BlinkActivity::BlinkActivity() : Activity("BlinkActivity", 2000) {
  isLightOn = false;
}

void BlinkActivity::update() {
  debug("Blink updating");
  if (isLightOn == true) {
    isLightOn = false;
    digitalWrite(LED_BUILTIN, 0);
  } else {
    isLightOn = true;
    digitalWrite(LED_BUILTIN, 1);
  }
}

void BlinkActivity::leftButtonPressed() {
}
void BlinkActivity::rightButtonPressed() {
}



////------------------------------------------------------------------ColorWheelActivity
ColorWheelActivity::ColorWheelActivity() : Activity("ColorWheelActivity", 10) {
  currentSpeed = 20; // The higher the number the slower
}

void ColorWheelActivity::update() {
  uint32_t offset = millis() / currentSpeed;
  for (int i = 0; i < 10; ++i) {
    CircuitPlayground.strip.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / 10) + offset) & 255));
  }
  // Show all the pixels.
  CircuitPlayground.strip.show();
}

void ColorWheelActivity::leftButtonPressed() {
  if(currentSpeed < 200) {
    currentSpeed += 5;
  }
  Serial.print("Current speed:  ");
  Serial.println(currentSpeed);
}
void ColorWheelActivity::rightButtonPressed() {
  if(currentSpeed > 5) {
    currentSpeed -= 5;
  }
  Serial.print("Current speed:  ");
  Serial.println(currentSpeed);
}


////------------------------------------------------------------------  Flashlight
FlashlightActivity::FlashlightActivity() : Activity("Flashlight", 1000) {
}

void FlashlightActivity::update() {
  resetDisplay();
  Serial.println("Flashlight updates");
  for (int x = 0; x <= 9; x++) {
    CircuitPlayground.strip.setPixelColor(x, 255,255,255);
  }
  CircuitPlayground.strip.show();
  
}

void FlashlightActivity::leftButtonPressed() {
}
void FlashlightActivity::rightButtonPressed() {
}




////-------------------------------------------------------------------- SoundActivity
SoundActivity::SoundActivity() : Activity("SoundActivity", 50) {
  maxLevel = 30;
}

void SoundActivity::update() {
  int16_t level = max(0, CircuitPlayground.soundSensor());
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  // Set the color based on the volume
  if (level > (maxLevel - 5)) {
    red = 255;
    green = 0;
    blue = 0;
  } else if (level > (maxLevel / 4) ) {
    red = 0;
    green = 200;
    blue = 0;
  } else if (maxLevel > 3) {
    red = 0;
    green = 0;
    blue = 100;
  } else {
    red = 0;
    green = 0;
    blue = 0;
  }

  CircuitPlayground.clearPixels();
  uint8_t pixels = map(level, 0, maxLevel, 0, 10);
  for (int pixel = 0; pixel < pixels; pixel++) {
    CircuitPlayground.setPixelColor(pixel, red, green, blue);
  }

  if (DEBUG_MODE == true) {
    sprintf(messageBuffer, "Sound: level=%d red=%d green=%d blue=%d pixels=%d maxLevel=%d", level, red, green, blue, pixels, maxLevel);
    debug(messageBuffer);
  }
}

void SoundActivity::leftButtonPressed() {
  if (maxLevel <= 50) {
    maxLevel += 5;
  }
}

void SoundActivity::rightButtonPressed() {
  if (maxLevel >= 5) {
    maxLevel -= 5;
  }
}

////-------------------------------------------------------------------- TemperatureActivity
TemperatureActivity::TemperatureActivity() : Activity("TemperatureActivity", 2000) {
}

void TemperatureActivity::update() {
  float tempF = CircuitPlayground.temperatureF();
  int pixelCount = map(tempF, 0, 110, 0, 10);
  int red = 0;
  int green = 0;

  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.println("Current temperature: ");
  oled.println(tempF);
  oled.println("");
  oled.println("Press Left or Right");
  oled.println("to end");
  oled.display();

  CircuitPlayground.clearPixels();
  for (int pixel = 0; pixel < pixelCount; pixel++) {
    red = map(pixel, 0, 9, 0, 255);
    green = map(pixel, 0, 9, 255, 0);
    CircuitPlayground.setPixelColor(pixel, red, green, 0);
  }

  if (DEBUG_MODE == true) {
    sprintf(messageBuffer, "Temperature  temp=%f pixelCount=%d ", tempF, pixelCount);
    debug(messageBuffer);
  }

}

void TemperatureActivity::leftButtonPressed() {
  Serial.println("Left pressed, resetting TemperatureActivity");
  currentActivity = &nullActivity;
  menuSystem.display();
}

void TemperatureActivity::rightButtonPressed() {
  Serial.println("Right pressed, resetting TemperatureActivity");
  currentActivity = &nullActivity;
  menuSystem.display();
}



////-------------------------------------------------------------------- SoundColorWheelActivity
SoundColorWheelActivity::SoundColorWheelActivity() : Activity("SoundColorWheelActivity", 5) {
  maxLevel = 8;
  currPixel = 0;
}

void SoundColorWheelActivity::update() {
  int16_t level = max(0, CircuitPlayground.soundSensor());
  boolean isUpdated = false;

  if (level > maxLevel) {
    currPixel = colorWheel(currPixel);
    isUpdated = true;
  }

  if (DEBUG_MODE == true) {
    sprintf(messageBuffer, "SoundColorWheelActivity: level=%d pixel=%d maxLevel=%d updated=%d", level, currPixel, maxLevel, isUpdated);
    debug(messageBuffer);
  }
}

void SoundColorWheelActivity::leftButtonPressed() {
  if (maxLevel <= 15) {
    maxLevel += 1;
  }
}

void SoundColorWheelActivity::rightButtonPressed() {
  if (maxLevel >= 1) {
    maxLevel -= 1;
  }
}



////-------------------------------------------------------------------- GeoActivity
GeoActivity::GeoActivity() : Activity("GeoActivity", 10) {
}

void GeoActivity::update() {
  x = CircuitPlayground.motionX();
  y = CircuitPlayground.motionY();
  z = CircuitPlayground.motionZ();

  Serial.print("X: "); Serial.print(x);
  Serial.print(" \tY: "); Serial.print(y);
  Serial.print(" \tZ: "); Serial.print(z);
  Serial.println(" m/s^2");

  for(int x=0 ; x<=9; x++) {
    CircuitPlayground.setPixelColor(x, 0,255,0);
  }
  
  if(x < threshholdMinus) {
   CircuitPlayground.setPixelColor(6, 255,0,0);
   CircuitPlayground.setPixelColor(7, 255,0,0);
   CircuitPlayground.setPixelColor(8, 255,0,0);
  } else if(x > threshholdPlus) {
   CircuitPlayground.setPixelColor(1, 255,0,0);
   CircuitPlayground.setPixelColor(2, 255,0,0);
   CircuitPlayground.setPixelColor(3, 255,0,0);
  }
  
  if(y < threshholdMinus) {
   CircuitPlayground.setPixelColor(0, 255,0,0);
   CircuitPlayground.setPixelColor(9, 255,0,0);
  } else if(y > threshholdPlus) {
   CircuitPlayground.setPixelColor(4, 255,0,0);
   CircuitPlayground.setPixelColor(5, 255,0,0);
  }
  
}

void GeoActivity::leftButtonPressed() {
}
void GeoActivity::rightButtonPressed() {
}
