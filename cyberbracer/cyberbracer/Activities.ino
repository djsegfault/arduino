////-------------------------------------------------------------------- Utility functions
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
NullActivity::NullActivity() : Activity("NullActivity", 0) {
}

void NullActivity::update() {
  debug("NulllActivity updates");
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
  debug("LightActivity updating");
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
