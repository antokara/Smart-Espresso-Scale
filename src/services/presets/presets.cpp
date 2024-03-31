#include <Arduino.h>
#include <EEPROM.h>
#include "services/presets/presets.h"
#include "services/device.h"
#include "modes/select_preset.h"

Preset *Presets::presets[PRESETS_COUNT];
byte Presets::presetIndex;
byte Presets::customBrewIndex = PRESETS_COUNT - 1;
int Presets::eeprom_address;

void Presets::setup()
{
    EEPROM.begin(EEPROM_SIZE_BYTES);
    Presets::eeprom_address = 0;
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
    // TODO:

    EEPROM.write(EEPROM_HAS_STORED_DATA_FLAG_ADDRESS, EEPROM_HAS_STORED_DATA_FLAG_VALUE);
    EEPROM.write(EEPROM_HAS_STORED_DATA_VER_ADDRESS, EEPROM_HAS_STORED_DATA_VER_VALUE);
    if (!EEPROM.commit())
    {
#ifdef SERIAL_DEBUG
        Serial.println("ERROR! EEPROM commit failed");
#endif
    }
}

/**
 * @brief sets the presets to their default values
 *
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
        Presets::presets[i]->autoPump = false;
    }
    // the last preset, will be dedicated custom brew preset
    Presets::presets[Presets::customBrewIndex]->name = "Custom Brew";
}

void Presets::load()
{
    // check and see if we have previously stored any data
    byte hasStoredData = EEPROM.read(EEPROM_HAS_STORED_DATA_FLAG_ADDRESS);
    byte hasStoredDataVersion = EEPROM.read(EEPROM_HAS_STORED_DATA_VER_ADDRESS);
    if (hasStoredData == EEPROM_HAS_STORED_DATA_FLAG_VALUE && hasStoredDataVersion == EEPROM_HAS_STORED_DATA_VER_VALUE)
    {
        // previously stored data of the same version
        // TODO: Load
    }
    else
    {
        // either no previous data stored OR version mismatch
        Presets::setDefault();
        Presets::save();
    }
}