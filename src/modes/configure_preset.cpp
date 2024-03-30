#include "services/lcd.h"
#include "modes/configure_preset.h"
#include "services/presets/presets.h"
#include "services/modes_controller.h"

byte Mode_Configure_Preset::presetIndex = 0;

modes Mode_Configure_Preset::getMode()
{
    return modes_configurePreset;
}

void Mode_Configure_Preset::setup()
{
    Mode_Configure_Preset::render();
}

void Mode_Configure_Preset::loop(){};

void Mode_Configure_Preset::render()
{
    Lcd::print("configure preset", 0, 0, clearLcd_all);
    Lcd::print(Presets::getPreset(Mode_Configure_Preset::presetIndex)->name, 0, 1);
};

void Mode_Configure_Preset::tare(button_states button_state)
{
    // NOP
}

void Mode_Configure_Preset::up(button_states button_state)
{
    if (button_state == button_pressed)
    {
        if (Mode_Configure_Preset::presetIndex < PRESETS_COUNT - 1)
        {
            Mode_Configure_Preset::presetIndex++;
        }
        else
        {
            Mode_Configure_Preset::presetIndex = 0;
        }
        Mode_Configure_Preset::render();
    }
}

void Mode_Configure_Preset::down(button_states button_state)
{
    if (button_state == button_pressed)
    {
        if (Mode_Configure_Preset::presetIndex > 0)
        {
            Mode_Configure_Preset::presetIndex--;
        }
        else
        {
            Mode_Configure_Preset::presetIndex = PRESETS_COUNT - 1;
        }
        Mode_Configure_Preset::render();
    }
}

void Mode_Configure_Preset::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Presets::presetIndex = Mode_Configure_Preset::presetIndex;
        Modes_Controller::setMode(modes_changePresetNameMenu);
    }
}

void Mode_Configure_Preset::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        Modes_Controller::setMode(modes_presetsMenu);
    }
}

void Mode_Configure_Preset::coffee(button_states button_state)
{
    // NOP
}
