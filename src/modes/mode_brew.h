#ifndef MODE_BREW
#define MODE_BREW
#include "modes/mode_base.h"
#include "modes/brew_stages.h"

// the weight the first drop needs to be
// in order for the brew timer to start
#define FIRST_DROP_WEIGHT 0.2

// the +/- delta of the
// estimated total brew weight,
// at the desired brew duration
// which qualifies as good.
// > means too fast
// < too slow
#define GOOD_BREW_WEIGHT_DELTA 0.3

// milliseconds that need to pass from the time
// the last drop was detected, to stop the brew timer
// when stopTimer == stopTimer_last_drop
#define TIME_SINCE_LAST_DROP_TO_STOP 2000

class Mode_Brew : public Mode_Base
{
public:
    void setup();
    void loop();
    void render();

    // sub nav (stages of brew)
    void setStage(brew_stages stage);
    brew_stages stage;

    // brew
    unsigned long brewStartTime;
    unsigned long timeAtLastDrop;
    unsigned int brewSeconds;
    float estBrewWeight;
    unsigned int estBrewSecondsLeft;
    float targetBrewWeight;
    byte estBrewSecondsLeftWarning;
    String getFormattedBrewSeconds();

    // user actions
    void tare();
    void up();
    void down();
    void ok();
    void cancel();
    void coffee();
};

#endif // MODE_BREW