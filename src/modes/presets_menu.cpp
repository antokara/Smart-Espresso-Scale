#include "modes/presets_menu.h"
#include "services/modes_controller.h"

modes Mode_Presets_Menu::getMode()
{
    return modes_presetsMenu;
}

void Mode_Presets_Menu::setup()
{
    Lcd::print("presets", 0, 0, clearLcd_all);
    Lcd::print(MENU_NAVIGATION, 0, 1);
};

void Mode_Presets_Menu::loop(){};

void Mode_Presets_Menu::tare(button_states button_state)
{
    // NOP
}

void Mode_Presets_Menu::up(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_customBrewMenu);
    }
}

void Mode_Presets_Menu::down(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_customBrewMenu);
    }
}

void Mode_Presets_Menu::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_configurePreset);
    }
}

void Mode_Presets_Menu::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_scale);
    }
}

void Mode_Presets_Menu::coffee(button_states button_state)
{
    // NOP
}
