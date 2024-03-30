#ifndef MODE_CUSTOM_BREW_CONFIRM
#define MODE_CUSTOM_BREW_CONFIRM
#include "modes/base.h"

class Mode_Custom_Brew_Confirm : public Mode_Base
{
public:
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

#endif // MODE_CUSTOM_BREW_CONFIRM