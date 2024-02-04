#include <Arduino.h>
#include "services/device.h"
#include "services/buzzer.h"
#include "services/lcd.h"
#include "services/scale.h"
#include "services/buttons.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"

void setup()
{
    Buzzer::setup();
    Lcd::setup();
    Scale::setup();
    Buttons::setup();
    Presets::setup();
    Modes_Controller::setup();
}

void loop()
{
    // services constantly run, regardless of the mode
    Buzzer::loop();
    Lcd::loop();
    Scale::loop();
    Buttons::loop();
    Modes_Controller::loop();
}
