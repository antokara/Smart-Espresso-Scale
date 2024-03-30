#ifndef MODE_BASE_VALUE_STEPPER
#define MODE_BASE_VALUE_STEPPER
#include "modes/base.h"

#define MAX_VALUE_STEPPER_STEPS 3

class Mode_Base_Value_Stepper : public Mode_Base
{
private:
    /**
     * @brief when was the first value change (button press)
     */
    unsigned long _firstValueChangeTime = 0;

    /**
     * @brief when was the last value change
     *
     */
    unsigned long _lastValueChangeTime = 0;

    /**
     * @brief the current value_steps[index]
     *
     */
    byte _value_step_index = 0;

protected:
    /**
     * @brief current value
     *
     */
    float value = 0;

    /**
     * @brief max allowed value
     *
     */
    float max_value = 50.0;

    /**
     * @brief min allowed value
     *
     */
    float min_value = 1.0;

    /**
     * @brief milliseconds that must pass while the button is still pressed
     *        before the value changes...
     *
     */
    int time_between_value_steps = 300;

    /**
     * @brief maximum number of value steps allowed
     *
     */
    byte max_value_steps = MAX_VALUE_STEPPER_STEPS;

    /**
     * @brief list of supported value steps
     *
     */
    float value_steps[MAX_VALUE_STEPPER_STEPS] = {};

    /**
     * @brief list of durations each value_step should
     *        be active, while the button is pressed,
     *        before increasing the value_step_index
     *
     */
    int value_step_durations[MAX_VALUE_STEPPER_STEPS - 1] = {1000, 2500};

public:
    Mode_Base_Value_Stepper()
    {
        this->value = 0;
        this->max_value = 50;
        this->min_value = 1;
        this->time_between_value_steps = 300;
        this->max_value_steps = 3;
        this->value_steps[0] = 0.1;
        this->value_steps[1] = 1;
        this->value_steps[2] = 5;
        this->value_step_durations[0] = 1000;
        this->value_step_durations[1] = 2500;
    }

    void up(button_states button_state);
    void down(button_states button_state);

    // standard methods (must be implemented by the derived class)
    virtual void value_step_up() = 0;
    virtual void value_step_down() = 0;
};

#endif // MODE_BASE_VALUE_STEPPER