#ifndef MODE_CUSTOM_BREW_MENU
#define MODE_CUSTOM_BREW_MENU
#include "modes/base.h"

class Mode_Custom_Brew_Menu : public Mode_Base
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

#endif // #define MODE_CUSTOM_BREW_MENU
