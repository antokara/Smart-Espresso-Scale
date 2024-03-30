#ifndef MODE_BASE_VALUE_STEPPER
#define MODE_BASE_VALUE_STEPPER
#include "modes/base.h"

class Mode_Base_Value_Stepper : public Mode_Base
{
private:
    /**
     * @brief when was the first value change (button press)
     */
    unsigned long _firstValueChangeTime;

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
    float value;

    /**
     * @brief max allowed value
     *
     */
    static constexpr float max_value = 50.0;

    /**
     * @brief min allowed value
     *
     */
    static constexpr float min_value = 1.0;

    /**
     * @brief milliseconds that must pass while the button is still pressed
     *        before the value changes...
     *
     */
    static const int time_between_value_steps = 300;

    /**
     * @brief maximum number of value steps allowed
     *
     */
    static const byte max_value_steps = 3;

    /**
     * @brief list of supported value steps
     *
     */
    const float value_steps[Mode_Base_Value_Stepper::max_value_steps] = {0.1, 1, 5};

    /**
     * @brief list of durations each value_step should
     *        be active, while the button is pressed,
     *        before increasing the value_step_index
     *
     */
    const int value_step_durations[Mode_Base_Value_Stepper::max_value_steps - 1] = {1000, 2500};

public:
    void up(button_states button_state);
    void down(button_states button_state);

    // standard methods (must be implemented by the derived class)
    virtual void value_step_up() = 0;
    virtual void value_step_down() = 0;
};

#endif // MODE_BASE_VALUE_STEPPER