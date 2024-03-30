#ifndef MODE_COFFEE_WEIGHT
#define MODE_COFFEE_WEIGHT
#include "modes/base.h"
#include "services/presets/presets.h"

#define MAX_VALUE 25.0
#define MIN_VALUE 5.0

/**
 * @brief milliseconds that must pass while the button is still pressed
 *        before the value changes...
 *
 */
#define VALUE_STEP_DURATION 300

/**
 * @brief maximum number of value steps in the list
 *
 */
#define MAX_VALUE_STEPS 3

class Mode_Coffee_Weight : public Mode_Base
{
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

    /**
     * @brief current coffee weight
     *
     */
    float _value;

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
     * @brief list of supported value steps
     *
     */
    const float _value_steps[MAX_VALUE_STEPS] = {0.1, 1, 5};

    /**
     * @brief list of durations each value_step should
     *        be active, while the button is pressed,
     *        before increasing the value_step_index
     *
     */
    const int _value_step_durations[MAX_VALUE_STEPS - 1] = {1000, 2500};

    /**
     * @brief the current value_steps[index]
     *
     */
    byte _value_step_index = 0;

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
    void up(button_states button_state);
    void down(button_states button_state);
    void ok(button_states button_state);
    void cancel(button_states button_state);
    void coffee(button_states button_state);
};

#endif // #define MODE_COFFEE_WEIGHT
