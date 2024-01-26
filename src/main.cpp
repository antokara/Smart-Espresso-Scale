#include <Arduino.h>
#include "device.h"
#include "lcd.h"
#include "scale.h"

void setup()
{
    Device::setup();
    Lcd::setup();
    Scale::setup();
}

void loop()
{
    Device::loop();
    Lcd::loop();
    Scale::loop();
}
