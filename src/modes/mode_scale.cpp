#include "modes/mode_scale.h"
#include "services/lcd.h"
#include "services/scale.h"
#include "services/buttons.h"
#include "services/modes_controller.h"

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
}

void Mode_Scale::tare()
{
    Modes_Controller::setMode(modes_tare);
    Lcd::print("tare    ", 0, 1);
}

void Mode_Scale::up()
{
}

void Mode_Scale::down()
{
}

void Mode_Scale::ok()
{
    Modes_Controller::setMode(modes_customBrewMenu);
}

void Mode_Scale::cancel()
{
}

void Mode_Scale::coffee()
{
    Modes_Controller::setMode(modes_selectPreset);
}
