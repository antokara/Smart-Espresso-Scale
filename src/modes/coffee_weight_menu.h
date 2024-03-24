#ifndef MODE_COFFEE_WEIGHT_MENU
#define MODE_COFFEE_WEIGHT_MENU
#include "modes/base.h"

class Mode_Coffee_Weight_Menu : public Mode_Base
{
public:
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

#endif // #define MODE_COFFEE_WEIGHT_MENU
