#include "modes/custom_brew_menu.h"
#include "services/modes_controller.h"

modes Mode_Custom_Brew_Menu::getMode()
{
    return modes_customBrewMenu;
}

void Mode_Custom_Brew_Menu::setup()
{
    Lcd::print("custom brew", 0, 0, clearLcd_all);
    Lcd::print(MENU_NAVIGATION, 0, 1);
};

void Mode_Custom_Brew_Menu::loop(){};

void Mode_Custom_Brew_Menu::tare(button_states button_state)
{
    // NOP
}

void Mode_Custom_Brew_Menu::up(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_presetsMenu);
    }
}

void Mode_Custom_Brew_Menu::down(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_presetsMenu);
    }
}

void Mode_Custom_Brew_Menu::ok(button_states button_state)
{
}

void Mode_Custom_Brew_Menu::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_scale);
    }
}

void Mode_Custom_Brew_Menu::coffee(button_states button_state)
{
    // NOP
}
