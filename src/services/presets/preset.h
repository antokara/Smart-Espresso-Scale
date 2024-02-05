#ifndef PRESET
#define PRESET
#include <Arduino.h>
#include "services/presets/startTimers.h"
#include "services/presets/stopTimers.h"

class Preset
{
public:
    String name;
    float coffeeWeight;
    float brewRatio;
    int brewDuration;
    startTimers startTimer;
    stopTimers stopTimer;
    bool autoPump;
};

#endif // PRESET
