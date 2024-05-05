#ifndef MODE_SELECT_PRESET
#define MODE_SELECT_PRESET
#include "modes/base.h"

class Mode_Select_Preset : public Mode_Base
{
public:
    modes getMode();
    void setup();
    void loop();
    void render();

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

#endif // MODE_SELECT_PRESET