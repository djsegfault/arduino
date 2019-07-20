/*
class MyRenderer : public MenuComponentRenderer {
public:
    void render(Menu const& menu) const {
        oled.clearDisplay();
        oled.setCursor(0, 0);

        if (menu.get_name() == "") {
            oled.println("Main Menu");
        } else {
            oled.println(menu.get_name());
        }

        for (int i = 0; i < menu.get_num_components(); ++i) {
            MenuComponent const* cp_m_comp = menu.get_menu_component(i);
            if (cp_m_comp->is_current()) {
                oled.print(">");
            } else {
                oled.print(" ");
            }
            cp_m_comp->render(*this);

            oled.println("");
        }
    }

    void render_menu_item(MenuItem const& menu_item) const {
        oled.print(menu_item.get_name());
    }

    void render_back_menu_item(BackMenuItem const& menu_item) const {
        oled.print(menu_item.get_name());
    }

    void render_numeric_menu_item(NumericMenuItem const& menu_item) const {
        oled.print(menu_item.get_name());
    }

    void render_menu(Menu const& menu) const {
        oled.print(menu.get_name());
    }
};
