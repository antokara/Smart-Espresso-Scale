#include "services/lcd.h"
#include "modes/start_timer.h"
#include "services/presets/presets.h"
#include "services/modes_controller.h"

modes Mode_Start_Timer::getMode()
{
    return modes_startTimer;
}

void Mode_Start_Timer::setup()
{
    this->startTimer = Presets::getPreset()->startTimer;
    this->Mode_Start_Timer::render();
}

void Mode_Start_Timer::loop(){};

void Mode_Start_Timer::render()
{
    Lcd::print("Start Timer when", 0, 0, clearLcd_all);

    String text = "";
    if (this->startTimer == startTimer_pump)
    {
        text = "Pump starts";
    }
    else if (this->startTimer == startTimer_first_drop)
    {
        text = "First Drop falls";
    }
    Lcd::print(text, 0, 1);
};

void Mode_Start_Timer::tare(button_states button_state)
{
    // NOP
}

void Mode_Start_Timer::up(button_states button_state)
{
    if (button_state == button_pressed)
    {
        if (this->startTimer == startTimer_pump)
        {
            this->startTimer = startTimer_first_drop;
        }
        else if (this->startTimer == startTimer_first_drop)
        {
            this->startTimer = startTimer_pump;
        }
        Mode_Start_Timer::render();
    }
}

void Mode_Start_Timer::down(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Mode_Start_Timer::up(button_state);
    }
}

void Mode_Start_Timer::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Presets::getPreset()->startTimer = this->startTimer;
        Presets::save();
        Modes_Controller::setMode(modes_startTimerMenu);
    }
}

void Mode_Start_Timer::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_startTimerMenu);
    }
}

void Mode_Start_Timer::coffee(button_states button_state)
{
    // NOP
}
