#include "services/scale.h"
#include "services/modes_controller.h"
#include "modes/mode_tare.h"

void Mode_Tare::setup()
{
    Scale::tare();
    Modes_Controller::setMode(modes_scale);
};

void Mode_Tare::loop(){};

void Mode_Tare::tare()
{
}

void Mode_Tare::up()
{
}

void Mode_Tare::down()
{
}

void Mode_Tare::ok()
{
}

void Mode_Tare::cancel()
{
}

void Mode_Tare::coffee()
{
}
