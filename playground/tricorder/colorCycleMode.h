
// See RainbowCycleDemo from mega_demo

void colorCycleSetup() {
  Serial.println("colorCycleSetup");

}

void colorCycleLoop() {
  uint32_t offset = millis() / current_speed;
  for (int i = 0; i < 10; ++i) {
    CircuitPlayground.strip.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / 10) + offset) & 255));
  }
  // Show all the pixels.
  CircuitPlayground.strip.show();
}
