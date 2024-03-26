#ifndef MODE_PRESETS_MENU
#define MODE_PRESETS_MENU
#include "modes/base.h"

class Mode_Presets_Menu : public Mode_Base
{
public:
    modes getMode();
    void setup();
    void loop();

    // user actions
    void tare(button_states button_state);
    void up(button_states button_state);
    void down(button_states button_state);
    void ok(button_states button_state);
    void cancel(button_states button_state);
    void coffee(button_states button_state);
};

#endif // #define MODE_PRESETS_MENU
