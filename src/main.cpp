#include <Arduino.h>
#include "device.h"
#include "buzzer.h"
#include "lcd.h"
#include "scale.h"
#include "buttons.h"

void setup()
{
    Buzzer::setup();
    Lcd::setup();
    Scale::setup();
    Buttons::setup();
}

void loop()
{
    Buzzer::loop();
    Lcd::loop();
    Scale::loop();
    Buttons::loop();
}
