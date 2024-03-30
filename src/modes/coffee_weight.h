#ifndef MODE_COFFEE_WEIGHT
#define MODE_COFFEE_WEIGHT
#include "modes/baseValueStepper.h"
#include "services/presets/presets.h"

class Mode_Coffee_Weight : public Mode_Base_Value_Stepper
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

public:
    Mode_Coffee_Weight(modes parentMode = modes_coffeeWeightMenu, modes okMode = modes_coffeeWeightMenu)
    {
        this->_parentMode = parentMode;
        this->_okMode = okMode;
        this->value = 0;
        this->max_value = 25;
        this->min_value = 5;
        this->max_value_steps = 3;
        this->value_steps[0] = 0.1;
        this->value_steps[1] = 1;
        this->value_steps[2] = 5;
        this->value_step_durations[0] = 1000;
        this->value_step_durations[1] = 2500;
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
