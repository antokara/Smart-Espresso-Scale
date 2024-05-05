#ifndef PRESETS
#define PRESETS
#include "services/presets/preset.h"

/**
 * @brief if this changes, you must also change the
 * DATA_STORE_VERSION_VALUE, which will cause the presets
 * to default their values but will prevent data corruption.
 */
#define PRESETS_COUNT 10

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
};

#endif // PRESETS