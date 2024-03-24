#ifndef MODE_CHANGE_PRESET_NAME
#define MODE_CHANGE_PRESET_NAME
#include "modes/base.h"

class Mode_Change_Preset_Name : public Mode_Base
{
public:
    modes getMode();
    void setup();
    void loop();
    void render();

    // user actions
    void tare();
    void up();
    void down();
    void ok();
    void cancel();
    void coffee();

private:
    static String name;
    static char character;
};

#endif // #define MODE_CHANGE_PRESET_NAME
