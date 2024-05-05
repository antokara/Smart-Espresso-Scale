#include "services/scale.h"
#include "services/modes_controller.h"
#include "modes/tare.h"
#include "services/lcd.h"
#include "services/buzzer.h"
#include "services/button_states.h"

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

void Mode_Tare::tare(button_states button_state)
{
}

void Mode_Tare::up(button_states button_state)
{
}

void Mode_Tare::down(button_states button_state)
{
}

void Mode_Tare::ok(button_states button_state)
{
}

void Mode_Tare::cancel(button_states button_state)
{
}

void Mode_Tare::coffee(button_states button_state)
{
}
