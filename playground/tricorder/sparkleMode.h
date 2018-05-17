void sparkleSetup() {
  randomSeed(42);
  Serial.println("colorCycleSetup");

}

void sparkleLoop() {
    int onPixel = random(0,9);
    int onColorR = random(0,255);
    int onColorG = random(0,255);
    int onColorB = random(0,255);
    for (int i = 0; i < 10; ++i) {
      if(i == onPixel) {
        CircuitPlayground.strip.setPixelColor(i, onColorR, onColorG, onColorB);
      } else {
        CircuitPlayground.strip.setPixelColor(i, 0, 0, 0);
      }
  }
  // Show all the pixels.
  CircuitPlayground.strip.show();
}
