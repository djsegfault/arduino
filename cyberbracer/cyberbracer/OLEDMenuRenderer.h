#ifndef OLEDMENURENDERER_H
#define OLEDMENURENDERER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


class OLEDMenuRenderer : public MenuComponentRenderer {

  private:
    Adafruit_SSD1306 oled = NULL;
    int pixels_wide = 0;
    int pixels_high = 0;
    boolean is_initialized = false;
  public:
    OLEDMenuRenderer(Adafruit_SSD1306 &oled, int pixels_wide, int pixels_high);
    /// void begin(Adafruit_SSD1306 &oled, int pixels_wide, int pixels_high);
    void render(Menu const& menu);
    void render_menu_item(MenuItem const& menu_item);
    void render_back_menu_item(BackMenuItem const& menu_item);
    void render_numeric_menu_item(NumericMenuItem const& menu_item) ;
    void render_menu(Menu const& menu);
};

#endif
