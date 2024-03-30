#include "modes/coffee_weight.h"
#include "modes/brew_ratio.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"
#include "services/scale.h"

modes Mode_Coffee_Weight::getMode()
{
    return modes_coffeeWeight;
}

void Mode_Coffee_Weight::setup()
{
    Lcd::print("coffee weight", 0, 0, clearLcd_all);
    this->value = Presets::getPreset()->coffeeWeight;
    Mode_Coffee_Weight::render();
};

void Mode_Coffee_Weight::loop(){};

void Mode_Coffee_Weight::render()
{
    Lcd::print(String(this->value) + SCALE_UNIT_SUFFIX_GRAMS, 0, 1, clearLcd_row);
};

void Mode_Coffee_Weight::tare(button_states button_state)
{
    // NOP
}

void Mode_Coffee_Weight::value_step_up()
{
    Mode_Coffee_Weight::render();
}

void Mode_Coffee_Weight::value_step_down()
{
    Mode_Coffee_Weight::render();
}

void Mode_Coffee_Weight::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Presets::getPreset()->coffeeWeight = this->value;
        Presets::save();
        if (this->_menu_mode == menu_modes_configurePreset)
        {
            Modes_Controller::setMode(modes_coffeeWeightMenu);
        }
        else if (this->_menu_mode == menu_modes_customBrew)
        {
            Modes_Controller::setMode(new Mode_Brew_Ratio(this->_menu_mode));
        }
    }
}

void Mode_Coffee_Weight::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        if (this->_menu_mode == menu_modes_configurePreset)
        {
            Modes_Controller::setMode(modes_coffeeWeightMenu);
        }
        else if (this->_menu_mode == menu_modes_customBrew)
        {
            Modes_Controller::setMode(modes_customBrewMenu);
        }
    }
}

void Mode_Coffee_Weight::coffee(button_states button_state)
{
    // NOP
}
