#include <Arduino.h>
#include "services/presets/presets.h"

Preset *Presets::presets[PRESETS_COUNT];

void Presets::setup()
{
    // TODO: load from flash
    for (byte i = 0; i < PRESETS_COUNT; i++)
    {
        Presets::presets[i] = new Preset();
        Presets::presets[i]->name = "Preset " + String(i + 1);
        Presets::presets[i]->brewDuration = 30;
        Presets::presets[i]->brewRatio = 2;
        Presets::presets[i]->coffeeWeight = 18;
        Presets::presets[i]->startTimer = startTimer_pump;
        Presets::presets[i]->stopTimer = stopTimer_last_drop;
        Presets::presets[i]->autoPump = false;
    }
}
