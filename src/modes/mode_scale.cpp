#include "modes/mode_scale.h"
#include "services/lcd.h"
#include "services/scale.h"
#include "services/buttons.h"
#include "services/modes_controller.h"

void Mode_Scale::setup()
{
    Lcd::print(Scale::getFormattedWeight(), 0, 0, clearLcd_all);
};

void Mode_Scale::loop()
{
    // TODO: make it a service?
    if (Scale::hasWeightChanged)
    {
        if (millis() - Mode_Scale::lastRender > LCD_REFRESH_RATE)
        {
            Lcd::print(Scale::getFormattedWeight(), 0, 0);
            Mode_Scale::lastRender = millis();
            Mode_Scale::bufferedRender = "";
        }
        else
        {
            Mode_Scale::bufferedRender = Scale::getFormattedWeight();
        }
    }
    else if (Mode_Scale::bufferedRender != "" && millis() - Mode_Scale::lastRender > LCD_REFRESH_RATE)
    {
        Lcd::print(Mode_Scale::bufferedRender, 0, 0);
        Mode_Scale::lastRender = millis();
        Mode_Scale::bufferedRender = "";
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
