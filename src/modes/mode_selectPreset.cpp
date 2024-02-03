#include <lcd.h>
#include <buttons.h>
#include <modes/modes_controller.h>
#include <modes/mode_selectPreset.h>

void Mode_SelectPreset::setup()
{
    Lcd::print("Select Preset", 0, 0, 1);
};

void Mode_SelectPreset::loop(){};

void Mode_SelectPreset::tare()
{
}

void Mode_SelectPreset::up()
{
}

void Mode_SelectPreset::down()
{
}

void Mode_SelectPreset::ok()
{
}

void Mode_SelectPreset::cancel()
{
    Modes_Controller::mode = modes_scale;
}

void Mode_SelectPreset::coffee()
{
}
