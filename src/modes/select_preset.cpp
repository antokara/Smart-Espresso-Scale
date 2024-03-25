#include "services/lcd.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"
#include "modes/select_preset.h"

byte Mode_Select_Preset::presetIndex = 0;

modes Mode_Select_Preset::getMode()
{
    return modes_selectPreset;
}

void Mode_Select_Preset::setup()
{
    Mode_Select_Preset::render();
};

void Mode_Select_Preset::loop(){};

void Mode_Select_Preset::render()
{
    Lcd::print("Select Preset", 0, 0, clearLcd_all);
    Lcd::print(Presets::getPreset()->name, 0, 1);
};

void Mode_Select_Preset::tare() {}

void Mode_Select_Preset::up()
{
    if (Mode_Select_Preset::presetIndex < PRESETS_COUNT - 1)
    {
        Mode_Select_Preset::presetIndex++;
    }
    else
    {
        Mode_Select_Preset::presetIndex = 0;
    }
    Presets::presetIndex = Mode_Select_Preset::presetIndex;
    Mode_Select_Preset::render();
}

void Mode_Select_Preset::down()
{
    if (Mode_Select_Preset::presetIndex > 0)
    {
        Mode_Select_Preset::presetIndex--;
    }
    else
    {
        Mode_Select_Preset::presetIndex = PRESETS_COUNT - 1;
    }
    Presets::presetIndex = Mode_Select_Preset::presetIndex;
    Mode_Select_Preset::render();
}

void Mode_Select_Preset::ok()
{
    Modes_Controller::setMode(modes_brew);
}

void Mode_Select_Preset::cancel()
{
    Modes_Controller::setMode(modes_scale);
}

void Mode_Select_Preset::coffee()
{
    Mode_Select_Preset::ok();
}
