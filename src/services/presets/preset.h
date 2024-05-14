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
    /**
     * @brief the number to use to multiply the predicted weight
     * of coffee which will be 1 second from "now", every 1/2 second.
     *
     * That, will give us the actual coffee weight, after the pump
     * stops and residual coffee stops dripping.
     *
     * Example:
     *  at second 29, we predict for second 30 (29+1),
     *  that the weight of the coffee, will be 37.9 gr.
     *  Our target is 18x2=36gr.
     *
     *  With a muliplier of 0.95 * 37.9 = 36gr.
     *
     *  So, at second 29 we must stop the pump, in order for the
     *  end result coffee weight, with the residual coffee drops,
     *  to reach the desired 36 gr.
     */
    float stopMultiplier;
};

#endif // PRESET
