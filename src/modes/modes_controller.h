#ifndef MODES_CONTROLLER
#define MODES_CONTROLLER
#include <Arduino.h>
#include <modes/modes.h>
#include <modes/mode_scale.h>
#include <modes/mode_tare.h>
#include <modes/mode_selectPreset.h>
#include <device.h>
#include <buttons.h>
#include <lcd.h>

class Modes_Controller
{
public:
    // properties
    static modes mode;
    static Mode_Scale modeScale;
    static Mode_Tare modeTare;
    static Mode_SelectPreset modeSelectPreset;

    // methods
    static void setup();
    static void loop();
};

#endif // MODES_CONTROLLER