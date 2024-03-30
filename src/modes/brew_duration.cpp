#include "modes/brew_duration.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"

modes Mode_Brew_Duration::getMode()
{
    return modes_brewDuration;
}

void Mode_Brew_Duration::setup()
{
    Lcd::print("brew duration", 0, 0, clearLcd_all);
    this->value = Presets::getPreset()->brewDuration;
    Mode_Brew_Duration::render();
};

void Mode_Brew_Duration::loop(){};

void Mode_Brew_Duration::render()
{
    Lcd::print(String(this->value) + " secs.", 0, 1, clearLcd_row);
};

void Mode_Brew_Duration::tare(button_states button_state)
{
    // NOP
}

void Mode_Brew_Duration::value_step_up()
{
    Mode_Brew_Duration::render();
}

void Mode_Brew_Duration::value_step_down()
{
    Mode_Brew_Duration::render();
}

void Mode_Brew_Duration::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Presets::getPreset()->brewDuration = this->value;
        Presets::save();
        if (this->_menu_mode == menu_modes_configurePreset)
        {
            Modes_Controller::setMode(modes_brewDurationMenu);
        }
        else if (this->_menu_mode == menu_modes_customBrew)
        {
            Modes_Controller::setMode(modes_customBrewConfirm);
        }
    }
}

void Mode_Brew_Duration::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        if (this->_menu_mode == menu_modes_configurePreset)
        {
            Modes_Controller::setMode(modes_brewDurationMenu);
        }
        else if (this->_menu_mode == menu_modes_customBrew)
        {
            Modes_Controller::setMode(modes_customBrewMenu);
        }
    }
}

void Mode_Brew_Duration::coffee(button_states button_state)
{
    // NOP
}
