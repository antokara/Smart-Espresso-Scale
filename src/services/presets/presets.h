#ifndef PRESETS
#define PRESETS
#include "services/presets/preset.h"

#define PRESETS_COUNT 10

class Presets
{
public:
    static Preset *presets[PRESETS_COUNT];
    static byte presetIndex;
    static Preset *getPreset(byte presetIndex = Presets::presetIndex);
    static void setup();
    static void save();
};

#endif // PRESETS