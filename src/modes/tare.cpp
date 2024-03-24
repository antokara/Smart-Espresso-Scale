#include "services/scale.h"
#include "services/modes_controller.h"
#include "modes/tare.h"
#include "services/lcd.h"
#include "services/buzzer.h"

modes Mode_Tare::getMode()
{
    return modes_tare;
}

void Mode_Tare::setup()
{
    // setup tare
    Buzzer::on();
    Lcd::print("Tearing...", 0, 0, clearLcd_all);

    // perform
    Scale::tare();

    // show zero to the screen
    Lcd::print(Scale::formatWeight(0), 0, 0, clearLcd_all);
    Buzzer::off();
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
