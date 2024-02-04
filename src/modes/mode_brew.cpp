#include "services/lcd.h"
#include "services/buttons.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"
#include "modes/mode_selectPreset.h"
#include "modes/mode_brew.h"

void Mode_Brew::setup()
{
    Mode_Brew::render();
};

void Mode_Brew::loop(){
    // TODO:
};

void Mode_Brew::render()
{
    // TODO:
    if (Mode_Brew::stage == brew_stage_in_progress)
    {
        Lcd::print("brew -progress-", 0, 0, 1);
    }
    else if (Mode_Brew::stage == brew_stage_stopping)
    {
        Lcd::print("brew -stopping-", 0, 0, 1);
    }
    else if (Mode_Brew::stage == brew_stage_done)
    {
        Lcd::print("brew -done-", 0, 0, 1);
    }
    Lcd::print(Presets::presets[Mode_SelectPreset::selectedPresetIndex]->name, 0, 1);
};

void Mode_Brew::tare() {}

void Mode_Brew::up()
{
}

void Mode_Brew::down()
{
}

void Mode_Brew::ok()
{
}

void Mode_Brew::setStage(brew_stages stage)
{
    if (Mode_Brew::stage != stage)
    {
        Mode_Brew::stage = stage;
        Buttons::ignoreAll();
        Mode_Brew::render();
        if (stage == brew_stage_stopping)
        {
            // TODO: stop the brew (toggle the relay switch)
        }
        }
}

void Mode_Brew::cancel()
{
    if (Mode_Brew::stage == brew_stage_in_progress)
    {
        // stop the brew
        Mode_Brew::setStage(brew_stage_stopping);
    }
    else
    {
        Modes_Controller::setMode(modes_scale);
    }
}

void Mode_Brew::coffee()
{
}
