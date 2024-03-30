#include "modes/brew_ratio.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"
#include "services/scale.h"

modes Mode_Brew_Ratio::getMode()
{
    return modes_brewRatio;
}

void Mode_Brew_Ratio::setup()
{
    Lcd::print("brew ratio", 0, 0, clearLcd_all);
    this->value = Presets::getPreset()->brewRatio;
    Mode_Brew_Ratio::render();
};

void Mode_Brew_Ratio::loop(){};

void Mode_Brew_Ratio::render()
{
    String brew_type = "";
    if (this->value < 2)
    {
        brew_type = "ristretto";
    }
    else if (this->value < 3)
    {
        brew_type = "trad/nal";
    }
    else if (this->value < 4)
    {
        brew_type = "lungo";
    }
    else
    {
        brew_type = "long";
    }

    Lcd::print(brew_type + " 1:" + String(this->value), 0, 1, clearLcd_row);
};

void Mode_Brew_Ratio::tare(button_states button_state)
{
    // NOP
}

void Mode_Brew_Ratio::value_step_up()
{
    Mode_Brew_Ratio::render();
}

void Mode_Brew_Ratio::value_step_down()
{
    Mode_Brew_Ratio::render();
}

void Mode_Brew_Ratio::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Presets::getPreset()->brewRatio = this->value;
        Presets::save();
        Modes_Controller::setMode(this->_okMode);
    }
}

void Mode_Brew_Ratio::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(this->_parentMode);
    }
}

void Mode_Brew_Ratio::coffee(button_states button_state)
{
    // NOP
}
