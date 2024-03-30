#include "services/lcd.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"
#include "modes/custom_brew_confirm.h"

modes Mode_Custom_Brew_Confirm::getMode()
{
    return modes_customBrewConfirm;
}

void Mode_Custom_Brew_Confirm::setup()
{
    Mode_Custom_Brew_Confirm::render();
};

void Mode_Custom_Brew_Confirm::loop(){};

void Mode_Custom_Brew_Confirm::render()
{
    Lcd::print("press OK to", 0, 0, clearLcd_all);
    Lcd::print("start brewing...", 0, 1);
};

void Mode_Custom_Brew_Confirm::tare(button_states button_state)
{
    // NOP
}

void Mode_Custom_Brew_Confirm::up(button_states button_state)
{
    // NOP
}

void Mode_Custom_Brew_Confirm::down(button_states button_state)
{
    // NOP
}

void Mode_Custom_Brew_Confirm::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_brew);
    }
}

void Mode_Custom_Brew_Confirm::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_customBrewMenu);
    }
}

void Mode_Custom_Brew_Confirm::coffee(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Mode_Custom_Brew_Confirm::ok(button_pressed);
    }
}
