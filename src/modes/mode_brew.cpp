#include "services/device.h"
#include "services/lcd.h"
#include "services/buttons.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"
#include "services/scale.h"
#include "modes/mode_selectPreset.h"
#include "modes/mode_brew.h"

/**
 * @brief sets the brewing stage (it's kind of a like a sub-mode)
 *
 * @param stage
 */
void Mode_Brew::setStage(brew_stages stage)
{
    if (Mode_Brew::stage != stage)
    {
#ifdef SERIAL_DEBUG
        Serial.print("Mode_Brew::setStage ");
        Serial.println(stage);
#endif
        Mode_Brew::stage = stage;
        Buttons::ignoreAll();
        Mode_Brew::render();
        if (stage == brew_stage_stopping)
        {
            if (
                Presets::presets[Mode_SelectPreset::selectedPresetIndex]->stopTimer == stopTimer_auto_pump ||
                Presets::presets[Mode_SelectPreset::selectedPresetIndex]->stopTimer == stopTimer_manual_pump)
            {
                // TODO: stop the brew (toggle the relay switch)
                Mode_Brew::setStage(brew_stage_done);
            }
        }
    }
}

void Mode_Brew::setup()
{
    Mode_Brew::setStage(brew_stage_waiting);
    // auto-tare right before we start, to negate the cup (that should already be on the scale)
    Scale::tare();
    Mode_Brew::render();
    if (Presets::presets[Mode_SelectPreset::selectedPresetIndex]->stopTimer == stopTimer_auto_pump)
    {
        Mode_Brew::setStage(brew_stage_in_progress);
        // TODO: start the brew (toggle the relay switch)
        // TODO: start the timer, if set on pump
    }
};

void Mode_Brew::loop()
{
    // TODO:
    if (Scale::hasWeightChanged)
    {
        if (Mode_Brew::stage == brew_stage_waiting && Presets::presets[Mode_SelectPreset::selectedPresetIndex]->startTimer == startTimer_first_drop)
        {
            Mode_Brew::setStage(brew_stage_in_progress);
            // TODO: start the timer, if set on first drop and not already started
        }
        Mode_Brew::render();
    }
    else if (Mode_Brew::stage == brew_stage_in_progress && Presets::presets[Mode_SelectPreset::selectedPresetIndex]->stopTimer == stopTimer_last_drop)
    {
        // TODO: detect timeout without a drop and if true, switch stage to done
    }
};

void Mode_Brew::render()
{
    Lcd::print("Brew " + Scale::getFormattedWeight(), 0, 0);
    if (Mode_Brew::stage == brew_stage_waiting && Presets::presets[Mode_SelectPreset::selectedPresetIndex]->startTimer == startTimer_manual_pump)
    {
        Lcd::print("Press Coffee...", 0, 1, clearLcd_row);
    }
    else if (Mode_Brew::stage == brew_stage_in_progress)
    {
        Lcd::print("1 second", 0, 1, clearLcd_row);
    }
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
    if (Mode_Brew::stage == brew_stage_waiting && Presets::presets[Mode_SelectPreset::selectedPresetIndex]->startTimer == startTimer_manual_pump)
    {
        Mode_Brew::setStage(brew_stage_in_progress);
    }
}
