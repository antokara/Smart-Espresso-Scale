#include "modes/stop_timer_menu.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"

modes Mode_Stop_Timer_Menu::getMode()
{
    return modes_stopTimerMenu;
}

void Mode_Stop_Timer_Menu::setup()
{
    Lcd::print("Stop Timer", 0, 0, clearLcd_all);
    Lcd::print(MENU_NAVIGATION, 0, 1);
};

void Mode_Stop_Timer_Menu::loop(){};

void Mode_Stop_Timer_Menu::tare(button_states button_state)
{
    // NOP
}

void Mode_Stop_Timer_Menu::up(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_startTimerMenu);
    }
}

void Mode_Stop_Timer_Menu::down(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_autoPumpMenu);
    }
}

void Mode_Stop_Timer_Menu::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_stopTimer);
    }
}

void Mode_Stop_Timer_Menu::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_configurePreset);
    }
}

void Mode_Stop_Timer_Menu::coffee(button_states button_state)
{
    // NOP
}
