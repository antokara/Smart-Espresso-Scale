#include "services/lcd.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"
#include "modes/mode_selectPreset.h"

byte Mode_SelectPreset::selectedPresetIndex = 0;

void Mode_SelectPreset::setup()
{
    Mode_SelectPreset::render();
};

void Mode_SelectPreset::loop(){};

void Mode_SelectPreset::render()
{
    Lcd::print("Select Preset", 0, 0, 1);
    Lcd::print(Presets::presets[Mode_SelectPreset::selectedPresetIndex]->name, 0, 1);
};

void Mode_SelectPreset::tare() {}

void Mode_SelectPreset::up()
{
    if (Mode_SelectPreset::selectedPresetIndex < PRESETS_COUNT - 1)
    {
        Mode_SelectPreset::selectedPresetIndex++;
    }
    else
    {
        Mode_SelectPreset::selectedPresetIndex = 0;
    }
    Mode_SelectPreset::render();
}

void Mode_SelectPreset::down()
{
    if (Mode_SelectPreset::selectedPresetIndex > 0)
    {
        Mode_SelectPreset::selectedPresetIndex--;
    }
    else
    {
        Mode_SelectPreset::selectedPresetIndex = PRESETS_COUNT - 1;
    }
    Mode_SelectPreset::render();
}

void Mode_SelectPreset::ok()
{
    Modes_Controller::setMode(modes_brew);
}

void Mode_SelectPreset::cancel()
{
    Modes_Controller::setMode(modes_scale);
}

void Mode_SelectPreset::coffee()
{
    Mode_SelectPreset::ok();
}
