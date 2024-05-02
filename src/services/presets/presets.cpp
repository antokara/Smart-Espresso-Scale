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
    // int eeprom_address = EEPROM_DATA_ADDRESS;
    // for (byte pi = 0; pi < PRESETS_COUNT; pi++)
    // {
    //     // Serial.print("preset: ");
    //     // Serial.println(Presets::presets[pi]->name);
    //     // for (byte vi = 0; vi < Presets::presets[pi]->name.length(); vi++)
    //     // {
    //     //     Serial.print(eeprom_address++);
    //     //     Serial.print(" ");
    //     //     // character
    //     //     Serial.print(Presets::presets[pi]->name.charAt(vi));
    //     //     Serial.print(" ");
    //     //     // ascii code of character
    //     //     Serial.println(int(Presets::presets[pi]->name.charAt(vi)));
    //     // }
    //     // Serial.print(eeprom_address++);
    //     // Serial.print(" ");
    //     // Serial.println(NULL, HEX);

    //     // byte bytes[4];
    //     // Data_Store::intToBytes(Presets::presets[pi]->brewDuration, bytes);
    //     // Serial.print("brewDuration: ");
    //     // Serial.println(Presets::presets[pi]->brewDuration);
    //     // for (int i = 0; i < 4; i++)
    //     // {
    //     //     Serial.print(eeprom_address++);
    //     //     Serial.print(" ");
    //     //     Serial.println(bytes[i]);
    //     // }

    //     // Presets::presets[i]->brewRatio = 2;
    //     // Presets::presets[i]->coffeeWeight = 17.8;
    //     // Presets::presets[i]->startTimer = startTimer_pump;
    //     // Presets::presets[i]->stopTimer = stopTimer_last_drop;
    //     // Presets::presets[i]->autoPump = false;
    // }

    //     EEPROM.write(DATA_STORE_HAS_STORED_DATA_FLAG_ADDRESS, DATA_STORE_HAS_STORED_DATA_FLAG_VALUE);
    //     EEPROM.write(EEPROM_VERSION_ADDRESS, DATA_STORE_VERSION_VALUE);
    //     if (!EEPROM.commit())
    //     {
    // #ifdef SERIAL_DEBUG
    //         Serial.println("ERROR! EEPROM commit failed");
    // #endif
    //     }
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
        Presets::presets[i]->autoPump = true;
    }
    // the last preset, will be dedicated custom brew preset
    Presets::presets[Presets::customBrewIndex]->name = "Custom Brew";
}

void Presets::load()
{
    Data_Store::writeByteData(15);
    Data_Store::writeBoolData(true);
    Data_Store::writeCharData('X');
    Data_Store::writeIntData(1024);
    Data_Store::writeFloatData(123.456);
    Data_Store::writeStringData("testing!");
    Data_Store::save();

    byte byte_val = Data_Store::readByteData();
    Serial.println("byte_val: ");
    Serial.println(byte_val);

    bool bool_val = Data_Store::readBoolData();
    Serial.println("bool_val: ");
    Serial.println(bool_val);

    // TODO: fix char read or write
    bool char_val = Data_Store::readCharData();
    Serial.println("char_val: ");
    Serial.println(char_val);

    int int_val = Data_Store::readIntData();
    Serial.println("int_val: ");
    Serial.println(int_val);

    // TODO: fix float read or write. we don't get the decimal points
    int float_val = Data_Store::readFloatData();
    Serial.println("float_val: ");
    Serial.println(float_val);

    String str_val = Data_Store::readStringData();
    Serial.println("str_val: ");
    Serial.println(str_val);

    // check and see if we have previously stored any data
    if (Data_Store::hasStoredData())
    {
        // previously stored data of the same version
        // TODO: Load
    }
    else
    {
        // either no previous data stored OR version mismatch
        // Presets::save();
    }
    Presets::setDefault();
}
