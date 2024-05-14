#ifndef STOP_MULTIPLIER
#define STOP_MULTIPLIER
#include "modes/baseValueStepper.h"
#include "services/presets/presets.h"
#include "modes/enums/menu_modes.h"

class Mode_Stop_Multiplier : public Mode_Base_Value_Stepper
{
private:
public:
    Mode_Stop_Multiplier()
    {
        this->value = 1;
        this->max_value = 2;
        this->min_value = 0;
        this->max_value_steps = 3;
        this->value_steps[0] = 0.01;
        this->value_steps[1] = 0.1;
        this->value_steps[2] = 0.5;
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

#endif // #define STOP_MULTIPLIER
