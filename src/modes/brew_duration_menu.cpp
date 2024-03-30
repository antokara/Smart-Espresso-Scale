#include "modes/brew_duration_menu.h"
#include "modes/brew_duration.h"
#include "modes/configure_preset.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"

modes Mode_Brew_Duration_Menu::getMode()
{
    return modes_brewDurationMenu;
}

void Mode_Brew_Duration_Menu::setup()
{
    Lcd::print("brew duration", 0, 0, clearLcd_all);
    Lcd::print(MENU_NAVIGATION, 0, 1);
};

void Mode_Brew_Duration_Menu::loop(){};

void Mode_Brew_Duration_Menu::tare(button_states button_state)
{
    // NOP
}

void Mode_Brew_Duration_Menu::up(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_brewRatioMenu);
    }
}

void Mode_Brew_Duration_Menu::down(button_states button_state)
{
    // TODO:
}

void Mode_Brew_Duration_Menu::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_brewDuration);
    }
}

void Mode_Brew_Duration_Menu::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_configurePreset);
    }
}

void Mode_Brew_Duration_Menu::coffee(button_states button_state)
{
    // NOP
}
