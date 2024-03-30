#ifndef MODE_CUSTOM_BREW_MENU
#define MODE_CUSTOM_BREW_MENU
#include "modes/base.h"

class Mode_Custom_Brew_Menu : public Mode_Base
{
public:
    modes getMode();
    void setup();
    void loop();

    /**
     * @brief static so that we can access that information
     * from other modes (even when this mode is not active)
     *
     */
    static byte presetIndex;

    // user actions
    void tare(button_states button_state);
    void up(button_states button_state);
    void down(button_states button_state);
    void ok(button_states button_state);
    void cancel(button_states button_state);
    void coffee(button_states button_state);
};

#endif // #define MODE_CUSTOM_BREW_MENU
