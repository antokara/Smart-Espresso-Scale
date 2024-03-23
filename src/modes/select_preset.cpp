#include "services/lcd.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"
#include "modes/select_preset.h"

byte Mode_Select_Preset::selectedPresetIndex = 0;

void Mode_Select_Preset::setup()
{
    Mode_Select_Preset::render();
};

void Mode_Select_Preset::loop(){};

void Mode_Select_Preset::render()
{
    Lcd::print("Select Preset", 0, 0, clearLcd_all);
    Lcd::print(Presets::presets[Mode_Select_Preset::selectedPresetIndex]->name, 0, 1);
};

void Mode_Select_Preset::tare() {}

void Mode_Select_Preset::up()
{
    if (Mode_Select_Preset::selectedPresetIndex < PRESETS_COUNT - 1)
    {
        Mode_Select_Preset::selectedPresetIndex++;
    }
    else
    {
        Mode_Select_Preset::selectedPresetIndex = 0;
    }
    Mode_Select_Preset::render();
}

void Mode_Select_Preset::down()
{
    if (Mode_Select_Preset::selectedPresetIndex > 0)
    {
        Mode_Select_Preset::selectedPresetIndex--;
    }
    else
    {
        Mode_Select_Preset::selectedPresetIndex = PRESETS_COUNT - 1;
    }
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
