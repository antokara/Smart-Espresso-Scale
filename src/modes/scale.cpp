#include "modes/scale.h"
#include "modes/tare.h"
#include "services/lcd.h"
#include "services/scale.h"
#include "services/buttons.h"
#include "services/modes_controller.h"
#include "services/power.h"

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
        Mode_Tare *mode_tare = new Mode_Tare();
        mode_tare->setup();
        delete mode_tare;
        Mode_Scale::firstSetup = false;
    }
    Lcd::print(Scale::getFormattedWeight(), 0, 0, clearLcd_all);
};

void Mode_Scale::loop()
{
    if (Scale::hasWeightChanged)
    {
        Mode_Scale::tryRenderNow(Scale::getFormattedWeight(), 0, 0);
        Power::trackActivity();
    }
    else
    {
        Mode_Scale::tryRenderBuffered();
    }
}

void Mode_Scale::tare(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Mode_Tare *mode_tare = new Mode_Tare();
        mode_tare->setup();
        delete mode_tare;
    }
}

void Mode_Scale::up(button_states button_state)
{
}

void Mode_Scale::down(button_states button_state)
{
}

void Mode_Scale::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_customBrewMenu);
    }
}

void Mode_Scale::cancel(button_states button_state)
{
}

void Mode_Scale::coffee(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_selectPreset);
    }
}
