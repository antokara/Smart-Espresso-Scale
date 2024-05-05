#include "modes/baseValueStepper.h"

void Mode_Base_Value_Stepper::up(button_states button_state)
{
    // when the user keeps the button down and
    // the value step index is still able to get increased and
    // enough time has passed
    if (button_state == button_down && this->_value_step_index < Mode_Base_Value_Stepper::max_value_steps - 1 && millis() - this->_firstValueChangeTime > this->value_step_durations[this->_value_step_index])
    {
        this->_value_step_index++;
    }

    // when the user just pressed the button OR
    // has kept the button down longer than the last value change time
    if (button_state == button_pressed || (button_state == button_down && millis() - this->_lastValueChangeTime > Mode_Base_Value_Stepper::time_between_value_steps))
    {
        // just pressed the button
        if (button_state == button_pressed)
        {
            this->_value_step_index = 0;
            this->_firstValueChangeTime = millis();
        }
        // always update this
        this->_lastValueChangeTime = millis();
        if (this->value + this->value_steps[this->_value_step_index] < Mode_Base_Value_Stepper::max_value)
        {
            // when the value can be increased within its bounds, increase it
            this->value += this->value_steps[this->_value_step_index];
            this->value_step_up();
        }
        else if (this->value < Mode_Base_Value_Stepper::max_value)
        {
            // otherwise, if it will overflow, set it to the max
            this->value = Mode_Base_Value_Stepper::max_value;
            this->value_step_up();
        }
    }
}

void Mode_Base_Value_Stepper::down(button_states button_state)
{
    // when the user keeps the button down and
    // the value step index is still able to get increased and
    // enough time has passed
    if (button_state == button_down && this->_value_step_index < Mode_Base_Value_Stepper::max_value_steps - 1 && millis() - this->_firstValueChangeTime > this->value_step_durations[this->_value_step_index])
    {
        this->_value_step_index++;
    }

    // when the user just pressed the button OR
    // has kept the button down longer than the last value change time
    if (button_state == button_pressed || (button_state == button_down && millis() - this->_lastValueChangeTime > Mode_Base_Value_Stepper::time_between_value_steps))
    {
        // just pressed the button
        if (button_state == button_pressed)
        {
            this->_value_step_index = 0;
            this->_firstValueChangeTime = millis();
        }
        // always update this
        this->_lastValueChangeTime = millis();
        if (this->value - this->value_steps[this->_value_step_index] > Mode_Base_Value_Stepper::min_value)
        {
            // when the value can be decreased within its bounds, decrease it
            this->value -= this->value_steps[this->_value_step_index];
            this->value_step_down();
        }
        else if (this->value > Mode_Base_Value_Stepper::min_value)
        {
            // otherwise, if it will overflow, set it to the min
            this->value = Mode_Base_Value_Stepper::min_value;
            this->value_step_down();
        }
    }
}