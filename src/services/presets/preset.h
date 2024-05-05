#ifndef PRESET
#define PRESET
#include <Arduino.h>
#include "services/presets/start_timers.h"
#include "services/presets/stop_timers.h"

class Preset
{
public:
    String name;
    float coffeeWeight;
    float brewRatio;
    int brewDuration;
    start_timers startTimer;
    stop_timers stopTimer;
    bool autoPump;
    // TODO: add stop offset (decide if it's time based or weight based)
};

#endif // PRESET
