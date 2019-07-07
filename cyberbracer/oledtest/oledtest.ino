#include <splash.h>
#include <Adafruit_SSD1306.h>

// Data Green 
#define SDA_PIN 9
// Clock yellow
#define SCL_PIN 8 

Adafruit_ssd1306syp display(SDA_PIN, SCL_PIN);
void setup()
{
  delay(1000);
  display.initialize();
}
void loop()
{
  display.clear();
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("DIYMALLS");
  display.update();
  delay(2000);
  display.clear();
}
