#include "modes/stop_multiplier.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"
#include "services/scale.h"

modes Mode_Stop_Multiplier::getMode()
{
    return modes_stopMultiplier;
}

void Mode_Stop_Multiplier::setup()
{
    this->value = Presets::getPreset()->stopMultiplier;
    Mode_Stop_Multiplier::render();
};

void Mode_Stop_Multiplier::loop() {};

void Mode_Stop_Multiplier::render()
{
    Lcd::print(String(this->value), 0, 1, clearLcd_row);
};

void Mode_Stop_Multiplier::tare(button_states button_state)
{
    // NOP
}

void Mode_Stop_Multiplier::value_step_up()
{
    Mode_Stop_Multiplier::render();
}

void Mode_Stop_Multiplier::value_step_down()
{
    Mode_Stop_Multiplier::render();
}

void Mode_Stop_Multiplier::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Presets::getPreset()->stopMultiplier = this->value;
        Presets::save();
        Modes_Controller::setMode(modes_stopMultiplierMenu);
    }
}

void Mode_Stop_Multiplier::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_stopMultiplierMenu);
    }
}

void Mode_Stop_Multiplier::coffee(button_states button_state)
{
    // NOP
}
