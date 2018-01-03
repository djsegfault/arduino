
void flashlightSetup() {
  Serial.println("flashlightSetup");
  for (int i = 0; i < 10; ++i) {
    CircuitPlayground.strip.setPixelColor(i, LED_MAX_BRIGHTNESS, LED_MAX_BRIGHTNESS, LED_MAX_BRIGHTNESS);
  }
  CircuitPlayground.setBrightness(LED_MAX_BRIGHTNESS);
  CircuitPlayground.strip.show();
}

void flashlightLoop() {
  // Everything is in setup

}
