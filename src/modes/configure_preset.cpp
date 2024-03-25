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
    Lcd::print(Presets::getPreset()->name, 0, 1);
};

void Mode_Configure_Preset::tare()
{
    // NOP
}

void Mode_Configure_Preset::up()
{
    if (Mode_Configure_Preset::presetIndex < PRESETS_COUNT - 1)
    {
        Mode_Configure_Preset::presetIndex++;
    }
    else
    {
        Mode_Configure_Preset::presetIndex = 0;
    }
    Presets::presetIndex = Mode_Configure_Preset::presetIndex;
    Mode_Configure_Preset::render();
}

void Mode_Configure_Preset::down()
{
    if (Mode_Configure_Preset::presetIndex > 0)
    {
        Mode_Configure_Preset::presetIndex--;
    }
    else
    {
        Mode_Configure_Preset::presetIndex = PRESETS_COUNT - 1;
    }
    Presets::presetIndex = Mode_Configure_Preset::presetIndex;
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
