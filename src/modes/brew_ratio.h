#ifndef MODE_BREW_RATIO
#define MODE_BREW_RATIO
#include "modes/baseValueStepper.h"
#include "services/presets/presets.h"
#include "modes/enums/menu_modes.h"

class Mode_Brew_Ratio : public Mode_Base_Value_Stepper
{
private:
    /**
     * @brief to know where to go when pressing ok/cancel/etc.
     *
     */
    menu_modes _menu_mode;

public:
    Mode_Brew_Ratio(menu_modes menu_mode = menu_modes_configurePreset)
    {
        this->_menu_mode = menu_mode;
        this->value = 0;
        this->max_value = 5;
        this->min_value = 1;
        this->max_value_steps = 2;
        this->value_steps[0] = 0.5;
        this->value_steps[1] = 1;
        this->value_step_durations[0] = 1000;
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

#endif // #define MODE_BREW_RATIO
