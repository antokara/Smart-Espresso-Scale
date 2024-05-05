#include <Arduino.h>
#include "services/device.h"
#include "services/buzzer.h"
#include "services/lcd.h"
#include "services/scale.h"
#include "services/buttons.h"
#include "services/power.h"
#include "services/ir.h"
#include "services/data_store.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"

void setup()
{
#ifdef SERIAL_DEBUG
    Serial.begin(9600);
    delay(2000);
#endif

    Data_Store::setup();
    Power::setup();
    Ir::setup();
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
    Power::loop();
    Ir::loop();
    Buzzer::loop();
    Lcd::loop();
    Scale::loop();
    Buttons::loop();
    Modes_Controller::loop();
}
