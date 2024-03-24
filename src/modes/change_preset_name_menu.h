#ifndef MODE_CHANGE_PRESET_NAME_MENU
#define MODE_CHANGE_PRESET_NAME_MENU
#include "modes/base.h"

class Mode_Change_Preset_Name_Menu : public Mode_Base
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

#endif // #define MODE_CHANGE_PRESET_NAME_MENU
