#ifndef MODE_COFFEE_WEIGHT
#define MODE_COFFEE_WEIGHT
#include "modes/baseValueStepper.h"
#include "services/presets/presets.h"

class Mode_Coffee_Weight : public Mode_Base_Value_Stepper
{
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
    static constexpr float max_value = 25.0;

    /**
     * @brief min allowed value
     *
     */
    static constexpr float min_value = 5.0;

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

private:
    /**
     * @brief where to go when pressing cancel/etc.
     *
     */
    modes _parentMode;

    /**
     * @brief where to go when pressing OK
     *
     */
    modes _okMode;

public:
    Mode_Coffee_Weight(modes parentMode = modes_coffeeWeightMenu, modes okMode = modes_coffeeWeightMenu)
    {
        this->_parentMode = parentMode;
        this->_okMode = okMode;
    }
    modes getMode();
    void setup();
    void loop();
    void render();

    // user actions
    void tare(button_states button_state);
    void ok(button_states button_state);
    void cancel(button_states button_state);
    void coffee(button_states button_state);
    void value_step_up();
    void value_step_down();
};

#endif // #define MODE_COFFEE_WEIGHT
