#ifndef MODE_COFFEE_WEIGHT
#define MODE_COFFEE_WEIGHT
#include "modes/base.h"
#include "services/presets/presets.h"

#define MAX_COFFEE_WEIGHT 5.0
#define MIN_COFFEE_WEIGHT 25.0

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
    static float coffee_weight;
    static float coffee_weight_step;

    // user actions
    void tare();
    void up();
    void down();
    void ok();
    void cancel();
    void coffee();
};

#endif // #define MODE_COFFEE_WEIGHT
