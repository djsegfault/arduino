
////-------------------------------------------------------------------- Animations
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
    sprintf(messageBuffer, "Update? %lu %lu %lu", currTime, lastUpdateTime, interval);
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

NullActivity::NullActivity() : Activity("NullActivity", 0) {
}

void NullActivity::update() {
  if (isTimeToUpdate()) {
    Activity::update();
    debug("NulllActivity updates");
  }
}

BlinkActivity::BlinkActivity() : Activity("BlinkActivity", 2000) {
  isLightOn = false;
}

void BlinkActivity::update() {
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
