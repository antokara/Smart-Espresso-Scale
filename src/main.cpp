#include <Arduino.h>
#include "device.h"
#include "buzzer.h"
#include "lcd.h"
#include "scale.h"
#include "buttons.h"
#include "modes/modes_controller.h"

void setup()
{
    Buzzer::setup();
    Lcd::setup();
    Scale::setup();
    Buttons::setup();
    Modes_Controller::setup();
}

void loop()
{
    Buzzer::loop();
    Lcd::loop();
    Scale::loop();
    Buttons::loop();
    Modes_Controller::loop();
}
