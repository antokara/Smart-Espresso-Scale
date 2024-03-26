#ifndef MODE_COFFEE_WEIGHT
#define MODE_COFFEE_WEIGHT
#include "modes/base.h"
#include "services/presets/presets.h"

#define MAX_COFFEE_WEIGHT 25.0
#define MIN_COFFEE_WEIGHT 5.0

#define DEFAULT_STEP 0.1
#define STEP_CHANGE_DURATION 500

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

    float _coffee_weight;
    float _coffee_weight_step = DEFAULT_STEP;
    unsigned long _firstButtonPressTime;
    unsigned long _lastChange = 0;

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
