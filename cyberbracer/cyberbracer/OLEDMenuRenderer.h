/*
   This class is an SSD1306 OLED display implementation of the renderer for
   Jon Black's arduino-menusystem library.  It is based on a pull request submitted by xunker
   implementing an OLED renderer, but mine is based on Adafruit libraries while his is based
   on the SSD1306Ascii library, which doesn't seem to be active.  I know Adafruit maintains
   and supports their libraries, so I support them.

   I have intentions of adding scaling to this, so menus with fewer options will be display in larger fonts,
   and menus with more options may be able to use two columns of options.

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

#ifndef OLEDMENURENDERER_H
#define OLEDMENURENDERER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


class OLEDMenuRenderer : public MenuComponentRenderer {
  public:
    void render(Menu const& menu) const;

    void render_menu_item(MenuItem const& menu_item) const;

    void render_back_menu_item(BackMenuItem const& menu_item) const;

    void render_numeric_menu_item(NumericMenuItem const& menu_item) const;

    void render_menu(Menu const& menu) const;
};

#endif
