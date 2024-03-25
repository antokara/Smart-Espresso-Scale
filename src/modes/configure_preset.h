#ifndef MODE_CONFIGURE_PRESET
#define MODE_CONFIGURE_PRESET
#include "modes/base.h"

class Mode_Configure_Preset : public Mode_Base
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
    void tare();
    void up();
    void down();
    void ok();
    void cancel();
    void coffee();
};

#endif // #define MODE_CONFIGURE_PRESET
