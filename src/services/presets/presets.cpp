#include <Arduino.h>
#include "services/presets/presets.h"
#include "services/device.h"
#include "services/data_store.h"
#include <services/data_store_types.h>
#include "modes/select_preset.h"

Preset *Presets::presets[PRESETS_COUNT];
byte Presets::presetIndex;
byte Presets::customBrewIndex = PRESETS_COUNT - 1;

void Presets::setup()
{
    Presets::load();
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
    for (byte i = 0; i < PRESETS_COUNT; i++)
    {
        Data_Store::writeStringData(Presets::presets[i]->name);
        Data_Store::writeIntData(Presets::presets[i]->brewDuration);
        Data_Store::writeFloatData(Presets::presets[i]->brewRatio);
        Data_Store::writeFloatData(Presets::presets[i]->coffeeWeight);
        Data_Store::writeIntData(Presets::presets[i]->startTimer);
        Data_Store::writeIntData(Presets::presets[i]->stopTimer);
        Data_Store::writeBoolData(Presets::presets[i]->autoPump);
        Data_Store::writeFloatData(Presets::presets[i]->stopMultiplier);
    }
    Data_Store::save();
}

/**
 * @brief sets the presets to their default values (in RAM)
 * but does not save them.
 */
void Presets::setDefault()
{
    for (byte i = 0; i < PRESETS_COUNT; i++)
    {
        Presets::presets[i] = new Preset();
        Presets::presets[i]->name = "Preset " + String(i + 1);
        Presets::presets[i]->brewDuration = 30;
        Presets::presets[i]->brewRatio = 2;
        Presets::presets[i]->coffeeWeight = 17.8;
        Presets::presets[i]->startTimer = startTimer_pump;
        Presets::presets[i]->stopTimer = stopTimer_last_drop;
        Presets::presets[i]->autoPump = true;
        Presets::presets[i]->stopMultiplier = 0.95;
    }
    // the last preset, will be dedicated custom brew preset
    Presets::presets[Presets::customBrewIndex]->name = "Custom Brew";
}

/**
 * @brief attempts to load previously saved presets, if they exist and
 * the data store versions match. Otherwise, it resets them to their
 * default values and saves them.
 */
void Presets::load()
{
    // check and see if we have previously stored any data
    if (Data_Store::hasStoredData())
    {
        // previously stored data of the same version
        for (byte i = 0; i < PRESETS_COUNT; i++)
        {
#ifdef SERIAL_DEBUG
            Serial.print("will load preset with index: ");
            Serial.println(i);
#endif
            Presets::presets[i] = new Preset();
            Presets::presets[i]->name = Data_Store::readStringData();
            Presets::presets[i]->brewDuration = Data_Store::readIntData();
            Presets::presets[i]->brewRatio = Data_Store::readFloatData();
            Presets::presets[i]->coffeeWeight = Data_Store::readFloatData();
            Presets::presets[i]->startTimer = static_cast<start_timers>(Data_Store::readIntData());
            Presets::presets[i]->stopTimer = static_cast<stop_timers>(Data_Store::readIntData());
            Presets::presets[i]->autoPump = Data_Store::readBoolData();
            Presets::presets[i]->stopMultiplier = Data_Store::readFloatData();
#ifdef SERIAL_DEBUG
            Serial.print("name: ");
            Serial.println(Presets::presets[i]->name);
            Serial.print("brewDuration: ");
            Serial.println(Presets::presets[i]->brewDuration);
            Serial.print("brewRatio: ");
            Serial.println(Presets::presets[i]->brewRatio);
            Serial.print("coffeeWeight: ");
            Serial.println(Presets::presets[i]->coffeeWeight);
            Serial.print("startTimer: ");
            Serial.println(Presets::presets[i]->startTimer);
            Serial.print("stopTimer: ");
            Serial.println(Presets::presets[i]->stopTimer);
            Serial.print("autoPump: ");
            Serial.println(Presets::presets[i]->autoPump);
            Serial.print("stopMultiplier: ");
            Serial.println(Presets::presets[i]->stopMultiplier);
#endif
        }
    }
    else
    {
        // either no previous data stored OR version mismatch
        Presets::setDefault();
        Presets::save();
    }
}
