#ifndef PRESET
#define PRESET
#include <Arduino.h>

enum startTimers
{
    startTimer_pump,
    startTimer_first_drop
};

enum stopTimers
{
    stopTimer_pump,
    stopTimer_last_drop
};

class Preset
{
public:
    String name;
    float coffeeWeight;
    float brewRatio;
    int brewDuration;
    startTimers startTimer;
    stopTimers stopTimer;
};

#endif // PRESET
