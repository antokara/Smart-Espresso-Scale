#include "modes/coffee_weight_menu.h"
#include "modes/coffee_weight.h"
#include "modes/configure_preset.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"

modes Mode_Coffee_Weight_Menu::getMode()
{
    return modes_coffeeWeightMenu;
}

void Mode_Coffee_Weight_Menu::setup()
{
    Lcd::print("coffee weight", 0, 0, clearLcd_all);
    Lcd::print(MENU_NAVIGATION, 0, 1);
};

void Mode_Coffee_Weight_Menu::loop(){};

void Mode_Coffee_Weight_Menu::tare(button_states button_state)
{
    // NOP
}

void Mode_Coffee_Weight_Menu::up(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_changePresetNameMenu);
    }
}

void Mode_Coffee_Weight_Menu::down(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_brewRatioMenu);
    }
}

void Mode_Coffee_Weight_Menu::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_coffeeWeight);
    }
}

void Mode_Coffee_Weight_Menu::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_configurePreset);
    }
}

void Mode_Coffee_Weight_Menu::coffee(button_states button_state)
{
    // NOP
}
