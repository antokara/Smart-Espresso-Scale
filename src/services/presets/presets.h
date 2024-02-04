#ifndef PRESETS
#define PRESETS
#include "services/presets/preset.h"

#define PRESETS_COUNT 10

class Presets
{
public:
    static Preset *presets[PRESETS_COUNT];
    static void setup();
};

#endif // PRESETS