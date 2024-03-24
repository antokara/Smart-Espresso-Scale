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
    void tare();
    void up();
    void down();
    void ok();
    void cancel();
    void coffee();
};

#endif // #define MODE_PRESETS_MENU
