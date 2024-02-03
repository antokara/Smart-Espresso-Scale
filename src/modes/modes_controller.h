#ifndef MODES_CONTROLLER
#define MODES_CONTROLLER
#include <modes/modes.h>
#include <modes/mode_base.h>
#include <modes/mode_scale.h>
#include <modes/mode_tare.h>
#include <modes/mode_selectPreset.h>

class Modes_Controller
{
public:
    // properties
    static modes mode;
    static modes prevMode;
    static Mode_Scale modeScale;
    static Mode_Tare modeTare;
    static Mode_SelectPreset modeSelectPreset;
    static Mode_Base *currentMode;

    // methods
    static void setup();
    static void loop();
};

#endif // MODES_CONTROLLER