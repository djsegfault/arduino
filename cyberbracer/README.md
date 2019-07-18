# Cyberbracer Cosplay Project
## David Kramer

This project was initially inspired by the arm-mounted computer on the predators in the Predator movies.  I decided to expand its usefulness by also making it useful for steampunk events, since I go to those too.  That affected the apperance and asthetics of it more than the functionality. For that reason, I decided to laser cut the housing out of wood instead of 3D printing a case.

## Electronic Components
- An Adafruit [Circuit Playground Express](https://learn.adafruit.com/adafruit-circuit-playground-express/overview) Arduino compatible, with all sorts of sensors and output devices, 10 NeoPixels, and switches.  In addition to the physical switches, this device has several capacitive touch switches, which I use in this project for the menus.
- A [.96" OLED display](https://www.amazon.com/Diymall-Yellow-Arduino-Display-Raspberry/dp/B00O2LLT30) based on the SSD1306 driver.  I chose one that interfaces with I2C, since it only required 2 data wires, and the Circuit Playground Express didn't have a lot of ports, and I was already using quite a few.
- A cheap cat toy laser pointer.  Conveniently, this also took 3 batteries totally 4.5v.  This was to simulate the targeting laser (though only 1 instead of 3) from the Predator.  I do have a high power green laser, but that would have made the cyberbracer banned from some events.
- A 3xAAA battery holder, providing 4.5v nominal to power the rest of the electronics.  I was intially concerned about using AAA batteries instead of the larger AA batteries, but I pretty hard power test program and it ran for about 40 hours straight, so... good enough for a convention ;)

## Functionality
This does not actually do anything useful; stating that off the bat. This is for cosplay fun only.  The main functionality is to monitor the many sensors on the Circuit Playground Express and alter the display on the RGB LED NeoPixels based on them.  The OLED display is used for the menu system to select the different modes.
