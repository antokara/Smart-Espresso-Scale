#ifndef MODE_SELECT_PRESET
#define MODE_SELECT_PRESET
#include <modes/mode_base.h>

class Mode_SelectPreset : public Mode_Base
{
public:
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

#endif // MODE_SELECT_PRESET