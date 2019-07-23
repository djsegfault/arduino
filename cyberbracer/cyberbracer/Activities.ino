
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
  sprintf(messageBuffer, "Update? %lu %lu %lu", currTime, lastUpdateTime, interval);
  Serial.println(messageBuffer);
  if ((lastUpdateTime == 0) || (currTime - lastUpdateTime > interval) ) {
    lastUpdateTime = currTime;
    return true;
  } else {
    return false;
  }
}

NullActivity::NullActivity() : Activity("NullActivity", 1000) {
}

void NullActivity::update() {
  Activity::update();
  debug("NulllActivity updates");
}

BlinkActivity::BlinkActivity() : Activity("BlinkActivity", 2000) {
  isLightOn = false;
}

void BlinkActivity::update() {
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
