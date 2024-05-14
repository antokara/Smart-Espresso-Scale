#include "modes/stop_multiplier_menu.h"
#include "modes/stop_multiplier.h"
#include "modes/configure_preset.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"

modes Mode_Stop_Multiplier_Menu::getMode()
{
    return modes_stopMultiplierMenu;
}

void Mode_Stop_Multiplier_Menu::setup()
{
    Lcd::print("Stop Multiplier", 0, 0, clearLcd_all);
    Lcd::print(MENU_NAVIGATION, 0, 1);
};

void Mode_Stop_Multiplier_Menu::loop() {};

void Mode_Stop_Multiplier_Menu::tare(button_states button_state)
{
    // NOP
}

void Mode_Stop_Multiplier_Menu::up(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_autoPumpMenu);
    }
}

void Mode_Stop_Multiplier_Menu::down(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_changePresetNameMenu);
    }
}

void Mode_Stop_Multiplier_Menu::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_stopMultiplier);
    }
}

void Mode_Stop_Multiplier_Menu::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_configurePreset);
    }
}

void Mode_Stop_Multiplier_Menu::coffee(button_states button_state)
{
    // NOP
}
