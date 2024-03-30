#include <Arduino.h>
#include "services/presets/presets.h"
#include "modes/select_preset.h"

Preset *Presets::presets[PRESETS_COUNT];
byte Presets::presetIndex;

void Presets::setup()
{
    // TODO: save/load from flash
    for (byte i = 0; i < PRESETS_COUNT; i++)
    {
        Presets::presets[i] = new Preset();
        Presets::presets[i]->name = "Preset " + String(i + 1);
        Presets::presets[i]->brewDuration = 30;
        Presets::presets[i]->brewRatio = 2;
        Presets::presets[i]->coffeeWeight = 18;
        Presets::presets[i]->startTimer = startTimer_pump;
        // Presets::presets[i]->startTimer = startTimer_first_drop;
        Presets::presets[i]->stopTimer = stopTimer_last_drop;
        Presets::presets[i]->autoPump = false;
    }
}

/**
 * @brief returns the currently selected preset.
 * this needs to be set prior to:
 *  - configuring a preset
 *  - brewing a preset
 *  - brewing a custom coffee brew
 *
 * @return Preset*
 */
Preset *Presets::getPreset(byte presetIndex)
{
    return Presets::presets[presetIndex];
}

/**
 * @brief saves all the presets in persistent storage
 *
 */
void Presets::save()
{
    // TODO:
}