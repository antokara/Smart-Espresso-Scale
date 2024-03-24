#ifndef MODE_COFFEE_WEIGHT
#define MODE_COFFEE_WEIGHT
#include "modes/base.h"

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

    // user actions
    void tare();
    void up();
    void down();
    void ok();
    void cancel();
    void coffee();
};

#endif // #define MODE_COFFEE_WEIGHT
