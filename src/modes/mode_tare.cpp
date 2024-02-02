#include <modes/mode_tare.h>
#include <scale.h>
#include <modes/modes_controller.h>

void Mode_Tare::loop()
{
    Serial.println("Mode_Tare::loop");
    Scale::tare();
    Modes_Controller::mode = scale;
};