#ifndef MODE_SELECT_PRESET
#define MODE_SELECT_PRESET
#include "modes/base.h"

class Mode_Select_Preset : public Mode_Base
{
public:
    void setup();
    void loop();
    void render();

    /**
     * @brief static so that we can access that information
     * from other modes (even when this mode is not active)
     *
     */
    static byte selectedPresetIndex;

    // user actions
    void tare();
    void up();
    void down();
    void ok();
    void cancel();
    void coffee();
};

#endif // MODE_SELECT_PRESET