#include "services/lcd.h"
#include "modes/stop_timer.h"
#include "services/presets/presets.h"
#include "services/modes_controller.h"

modes Mode_Stop_Timer::getMode()
{
    return modes_stopTimer;
}

void Mode_Stop_Timer::setup()
{
    this->stopTimer = Presets::getPreset()->stopTimer;
    this->Mode_Stop_Timer::render();
}

void Mode_Stop_Timer::loop(){};

void Mode_Stop_Timer::render()
{
    Lcd::print("Stop Timer when", 0, 0, clearLcd_all);

    String text = "";
    if (this->stopTimer == stopTimer_pump)
    {
        text = "Pump stops";
    }
    else if (this->stopTimer == stopTimer_last_drop)
    {
        text = "Last Drop falls";
    }
    Lcd::print(text, 0, 1);
};

void Mode_Stop_Timer::tare(button_states button_state)
{
    // NOP
}

void Mode_Stop_Timer::up(button_states button_state)
{
    if (button_state == button_pressed)
    {
        if (this->stopTimer == stopTimer_pump)
        {
            this->stopTimer = stopTimer_last_drop;
        }
        else if (this->stopTimer == stopTimer_last_drop)
        {
            this->stopTimer = stopTimer_pump;
        }
        Mode_Stop_Timer::render();
    }
}

void Mode_Stop_Timer::down(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Mode_Stop_Timer::up(button_state);
    }
}

void Mode_Stop_Timer::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Presets::getPreset()->stopTimer = this->stopTimer;
        Presets::save();
        Modes_Controller::setMode(modes_stopTimerMenu);
    }
}

void Mode_Stop_Timer::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_stopTimerMenu);
    }
}

void Mode_Stop_Timer::coffee(button_states button_state)
{
    // NOP
}
