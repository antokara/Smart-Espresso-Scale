#include <modes/mode_tare.h>
#include <scale.h>
#include <modes/modes_controller.h>

void Mode_Tare::setup()
{
    Scale::tare();
    Modes_Controller::mode = scale;
};

void Mode_Tare::loop(){};