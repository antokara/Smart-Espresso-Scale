#include <Arduino.h>
#include "device.h"
#include "lcd.h"

void setup()
{
    Device::setup();
    Lcd::setup();
}

void loop()
{
    Device::loop();
    Lcd::loop();
}
