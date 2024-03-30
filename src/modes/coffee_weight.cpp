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
    this->_firstValueChangeTime = 0;
    this->_lastValueChangeTime = 0;
    this->_value_step_index = 0;
    this->_value = Presets::getPreset()->coffeeWeight;
    Mode_Coffee_Weight::render();
};

void Mode_Coffee_Weight::loop(){};

void Mode_Coffee_Weight::render()
{
    Lcd::print(String(this->_value) + SCALE_UNIT_SUFFIX_GRAMS, 0, 1, clearLcd_row);
};

void Mode_Coffee_Weight::tare(button_states button_state)
{
    // NOP
}

void Mode_Coffee_Weight::up(button_states button_state)
{
    // when the user keeps the button down and
    // the value step index is still able to get increased and
    // enough time has passed
    if (button_state == button_down && this->_value_step_index < MAX_VALUE_STEPS - 1 && millis() - this->_firstValueChangeTime > this->_value_step_durations[this->_value_step_index])
    {
        this->_value_step_index++;
    }

    // when the user just pressed the button OR
    // has kept the button down longer than the last value change time
    if (button_state == button_pressed || (button_state == button_down && millis() - this->_lastValueChangeTime > VALUE_STEP_DURATION))
    {
        // just pressed the button
        if (button_state == button_pressed)
        {
            this->_value_step_index = 0;
            this->_firstValueChangeTime = millis();
        }
        // always update this
        this->_lastValueChangeTime = millis();
        if (this->_value + this->_value_steps[this->_value_step_index] < MAX_VALUE)
        {
            // when the value can be increased within its bounds, increase it
            this->_value += this->_value_steps[this->_value_step_index];
            Mode_Coffee_Weight::render();
        }
        else if (this->_value < MAX_VALUE)
        {
            // otherwise, if it will overflow, set it to the max
            this->_value = MAX_VALUE;
            Mode_Coffee_Weight::render();
        }
    }
}

void Mode_Coffee_Weight::down(button_states button_state)
{
    // when the user keeps the button down and
    // the value step index is still able to get increased and
    // enough time has passed
    if (button_state == button_down && this->_value_step_index < MAX_VALUE_STEPS - 1 && millis() - this->_firstValueChangeTime > this->_value_step_durations[this->_value_step_index])
    {
        this->_value_step_index++;
    }

    // when the user just pressed the button OR
    // has kept the button down longer than the last value change time
    if (button_state == button_pressed || (button_state == button_down && millis() - this->_lastValueChangeTime > VALUE_STEP_DURATION))
    {
        // just pressed the button
        if (button_state == button_pressed)
        {
            this->_value_step_index = 0;
            this->_firstValueChangeTime = millis();
        }
        // always update this
        this->_lastValueChangeTime = millis();
        if (this->_value - this->_value_steps[this->_value_step_index] > MIN_VALUE)
        {
            // when the value can be decreased within its bounds, decrease it
            this->_value -= this->_value_steps[this->_value_step_index];
            Mode_Coffee_Weight::render();
        }
        else if (this->_value > MIN_VALUE)
        {
            // otherwise, if it will overflow, set it to the min
            this->_value = MIN_VALUE;
            Mode_Coffee_Weight::render();
        }
    }
}

void Mode_Coffee_Weight::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Presets::getPreset()->coffeeWeight = this->_value;
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
