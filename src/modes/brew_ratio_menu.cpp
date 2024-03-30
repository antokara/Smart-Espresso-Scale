#include "modes/brew_ratio_menu.h"
#include "modes/brew_ratio.h"
#include "modes/configure_preset.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"

modes Mode_Brew_Ratio_Menu::getMode()
{
    return modes_brewRatioMenu;
}

void Mode_Brew_Ratio_Menu::setup()
{
    Lcd::print("brew ratio", 0, 0, clearLcd_all);
    Lcd::print(MENU_NAVIGATION, 0, 1);
};

void Mode_Brew_Ratio_Menu::loop(){};

void Mode_Brew_Ratio_Menu::tare(button_states button_state)
{
    // NOP
}

void Mode_Brew_Ratio_Menu::up(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_coffeeWeightMenu);
    }
}

void Mode_Brew_Ratio_Menu::down(button_states button_state)
{
    // TODO:
}

void Mode_Brew_Ratio_Menu::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Presets::presetIndex = Mode_Configure_Preset::presetIndex;
        Modes_Controller::setMode(modes_brewRatio);
    }
}

void Mode_Brew_Ratio_Menu::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_configurePreset);
    }
}

void Mode_Brew_Ratio_Menu::coffee(button_states button_state)
{
    // NOP
}
