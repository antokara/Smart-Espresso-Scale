#include <modes/mode_tare.h>
#include <scale.h>
#include <modes/modes_controller.h>

void Mode_Tare::setup()
{
    Serial.println("Mode_Tare::setup()");
    Scale::tare();
    Modes_Controller::mode = modes_scale;
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
