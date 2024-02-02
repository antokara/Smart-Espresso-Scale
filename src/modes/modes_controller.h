#ifndef MODES_CONTROLLER
#define MODES_CONTROLLER
#include <Arduino.h>
#include <modes/modes.h>
#include <modes/mode_scale.h>
#include <modes/mode_tare.h>
#include <device.h>

class Modes_Controller
{
public:
    // properties
    static modes mode;
    static Mode_Scale modeScale;
    static Mode_Tare modeTare;

    // methods
    static void setup();
    static void loop();
};

#endif // MODES_CONTROLLER