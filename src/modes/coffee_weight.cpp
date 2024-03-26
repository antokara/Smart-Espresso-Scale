#include "modes/coffee_weight.h"
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
    this->_coffee_weight = Presets::getPreset()->coffeeWeight;
    Mode_Coffee_Weight::render();
};

void Mode_Coffee_Weight::loop(){};

void Mode_Coffee_Weight::render()
{
    Lcd::print(String(this->_coffee_weight) + SCALE_UNIT_SUFFIX_GRAMS, 0, 1, clearLcd_row);
};

void Mode_Coffee_Weight::tare(button_states button_state)
{
    // NOP
}

void Mode_Coffee_Weight::up(button_states button_state)
{
    if (button_state == button_down && millis() - this->_firstButtonPressTime > STEP_CHANGE_DURATION)
    {
        this->_coffee_weight_step = 1;
    }

    if (button_state == button_pressed || (button_state == button_down && millis() - this->_lastChange > STEP_CHANGE_DURATION))
    {
        if (button_state == button_pressed)
        {
            this->_coffee_weight_step = DEFAULT_STEP;
            this->_firstButtonPressTime = millis();
        }
        this->_lastChange = millis();
        if (this->_coffee_weight + this->_coffee_weight_step < MAX_COFFEE_WEIGHT)
        {
            this->_coffee_weight += this->_coffee_weight_step;
            Mode_Coffee_Weight::render();
        }
    }
}

void Mode_Coffee_Weight::down(button_states button_state)
{
    if (button_state == button_down && millis() - this->_firstButtonPressTime > STEP_CHANGE_DURATION)
    {
        this->_coffee_weight_step = 1;
    }

    if (button_state == button_pressed || (button_state == button_down && millis() - this->_lastChange > STEP_CHANGE_DURATION))
    {
        if (button_state == button_pressed)
        {
            this->_coffee_weight_step = DEFAULT_STEP;
            this->_firstButtonPressTime = millis();
        }
        this->_lastChange = millis();
        if (this->_coffee_weight - this->_coffee_weight_step > MIN_COFFEE_WEIGHT)
        {
            this->_coffee_weight -= this->_coffee_weight_step;
            Mode_Coffee_Weight::render();
        }
    }
}

void Mode_Coffee_Weight::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Presets::getPreset()->coffeeWeight = this->_coffee_weight;
        Presets::save();
        Modes_Controller::setMode(this->_okMode);
    }
}

void Mode_Coffee_Weight::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(this->_parentMode);
    }
}

void Mode_Coffee_Weight::coffee(button_states button_state)
{
    // NOP
}
