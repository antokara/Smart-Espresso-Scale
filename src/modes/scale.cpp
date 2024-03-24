#include "modes/scale.h"
#include "modes/tare.h"
#include "services/lcd.h"
#include "services/scale.h"
#include "services/buttons.h"
#include "services/modes_controller.h"

bool Mode_Scale::firstSetup = true;

modes Mode_Scale::getMode()
{
    return modes_scale;
}

void Mode_Scale::setup()
{
    // only tare on the first setup of the scale mode...
    if (Mode_Scale::firstSetup)
    {
        (new Mode_Tare())->setup();
        Mode_Scale::firstSetup = false;
    }
    Lcd::print(Scale::getFormattedWeight(), 0, 0, clearLcd_all);
};

void Mode_Scale::loop()
{
    if (Scale::hasWeightChanged)
    {
        Mode_Scale::tryRenderNow(Scale::getFormattedWeight(), 0, 0);
    }
    else
    {
        Mode_Scale::tryRenderBuffered();
    }
}

void Mode_Scale::tare()
{
    Modes_Controller::setMode(modes_tare);
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
