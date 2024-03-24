#include "services/lcd.h"
#include "modes/configure_preset.h"
#include "services/presets/presets.h"
#include "services/modes_controller.h"

byte Mode_Configure_Preset::selectedPresetIndex = 0;

void Mode_Configure_Preset::setup()
{
    Mode_Configure_Preset::render();
}

void Mode_Configure_Preset::loop(){};

void Mode_Configure_Preset::render()
{
    Lcd::print("configure preset", 0, 0, clearLcd_all);
    Lcd::print(Presets::presets[Mode_Configure_Preset::selectedPresetIndex]->name, 0, 1);
};

void Mode_Configure_Preset::tare()
{
    // NOP
}

void Mode_Configure_Preset::up()
{
    if (Mode_Configure_Preset::selectedPresetIndex < PRESETS_COUNT - 1)
    {
        Mode_Configure_Preset::selectedPresetIndex++;
    }
    else
    {
        Mode_Configure_Preset::selectedPresetIndex = 0;
    }
    Mode_Configure_Preset::render();
}

void Mode_Configure_Preset::down()
{
    if (Mode_Configure_Preset::selectedPresetIndex > 0)
    {
        Mode_Configure_Preset::selectedPresetIndex--;
    }
    else
    {
        Mode_Configure_Preset::selectedPresetIndex = PRESETS_COUNT - 1;
    }
    Mode_Configure_Preset::render();
}

void Mode_Configure_Preset::ok()
{
    Modes_Controller::setMode(modes_changePresetNameMenu);
}

void Mode_Configure_Preset::cancel()
{
    Modes_Controller::setMode(modes_presetsMenu);
}

void Mode_Configure_Preset::coffee()
{
    // NOP
}
