#ifndef PRESETS
#define PRESETS
#include "services/presets/preset.h"

#define PRESETS_COUNT 10

/**
 * @brief max. number of bytes we can store in EEPROM
 *        about 34 bytes per preset
 *        x10 presets, that is a total of 340 bytes
 */
// TODO: check if we can use sizeof here
#define EEPROM_SIZE_BYTES 512

/**
 * @brief mem. address of the flag that let's us know
 * if we have previously stored any data
 *
 */
#define EEPROM_HAS_STORED_DATA_FLAG_ADDRESS 0

/**
 * @brief the value to look for in mem. to know that we
 * have previously stored data
 */
#define EEPROM_HAS_STORED_DATA_FLAG_VALUE 125

/**
 * @brief mem. address of the flag that let's us know
 * what version of data we have previously stored
 *
 */
#define EEPROM_HAS_STORED_DATA_VER_ADDRESS 1
/**
 * @brief version of data previously stored
 * e.g. in case we make a breaking change in the data structure,
 * we need to overwrite with defaults...
 *
 */
#define EEPROM_HAS_STORED_DATA_VER_VALUE 1

#define EEPROM_DATA_ADDRESS 2

class Presets
{
public:
    static Preset *presets[PRESETS_COUNT];
    static byte presetIndex;
    static byte customBrewIndex;
    static Preset *getPreset(byte presetIndex = Presets::presetIndex);
    static void setup();
    static void save();
    static void load();
    static void setDefault();

    static int eeprom_address;
};

#endif // PRESETS