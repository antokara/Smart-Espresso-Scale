#include <modes/mode_scale.h>
#include <lcd.h>
#include <scale.h>
#include <buttons.h>
#include <modes/modes_controller.h>

void Mode_Scale::setup()
{
    Lcd::clear();
};

void Mode_Scale::loop()
{
    if (Scale::hasWeightChanged)
    {
        // TODO: debounce the screen updates because the LCD has a very slow refresh rate
        //       the last value, must be retained/shown eventually...
        Lcd::print(Scale::formatWeight(Scale::getWeight()), 0, 0);
    }

    if (Buttons::tare == button_pressed)
    {
        Modes_Controller::mode = tare;
    }
    else if (Buttons::ok == button_pressed)
    {
        Modes_Controller::mode = customBrewMenu;
    }
    else if (Buttons::coffee == button_pressed)
    {
        Modes_Controller::mode = selectPreset;
    }
};
