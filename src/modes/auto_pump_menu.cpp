#include "modes/auto_pump_menu.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"

modes Mode_Auto_Pump_Menu::getMode()
{
    return modes_autoPumpMenu;
}

void Mode_Auto_Pump_Menu::setup()
{
    Lcd::print("Auto Pump", 0, 0, clearLcd_all);
    Lcd::print(MENU_NAVIGATION, 0, 1);
};

void Mode_Auto_Pump_Menu::loop(){};

void Mode_Auto_Pump_Menu::tare(button_states button_state)
{
    // NOP
}

void Mode_Auto_Pump_Menu::up(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_stopTimerMenu);
    }
}

void Mode_Auto_Pump_Menu::down(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_changePresetNameMenu);
    }
}

void Mode_Auto_Pump_Menu::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_autoPump);
    }
}

void Mode_Auto_Pump_Menu::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_configurePreset);
    }
}

void Mode_Auto_Pump_Menu::coffee(button_states button_state)
{
    // NOP
}
