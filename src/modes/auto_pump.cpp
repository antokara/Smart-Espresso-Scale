#include "services/lcd.h"
#include "modes/auto_pump.h"
#include "services/presets/presets.h"
#include "services/modes_controller.h"

modes Mode_Auto_Pump::getMode()
{
    return modes_autoPump;
}

void Mode_Auto_Pump::setup()
{
    this->autoPump = Presets::getPreset()->autoPump;
    this->Mode_Auto_Pump::render();
}

void Mode_Auto_Pump::loop(){};

void Mode_Auto_Pump::render()
{
    Lcd::print("Auto Pump", 0, 0, clearLcd_all);
    Lcd::print(this->autoPump ? "Enabled" : "Disabled", 0, 1);
};

void Mode_Auto_Pump::tare(button_states button_state)
{
    // NOP
}

void Mode_Auto_Pump::up(button_states button_state)
{
    if (button_state == button_pressed)
    {
        this->autoPump = !this->autoPump;
        Mode_Auto_Pump::render();
    }
}

void Mode_Auto_Pump::down(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Mode_Auto_Pump::up(button_state);
    }
}

void Mode_Auto_Pump::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Presets::getPreset()->autoPump = this->autoPump;
        Presets::save();
        Modes_Controller::setMode(modes_autoPumpMenu);
    }
}

void Mode_Auto_Pump::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_autoPumpMenu);
    }
}

void Mode_Auto_Pump::coffee(button_states button_state)
{
    // NOP
}
