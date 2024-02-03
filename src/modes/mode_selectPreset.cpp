#include <lcd.h>
#include <buttons.h>
#include <modes/modes_controller.h>
#include <modes/mode_selectPreset.h>

void Mode_SelectPreset::setup()
{
    Lcd::print("Select Preset", 0, 0, 1);
};

void Mode_SelectPreset::loop()
{
    if (Buttons::cancel == button_pressed)
    {
        Modes_Controller::mode = scale;
    }
};
