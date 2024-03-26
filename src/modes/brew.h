#ifndef MODE_BREW
#define MODE_BREW
#include "modes/base.h"
#include "modes/enums/brew_stages.h"

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

// the minimum weight during brew (greater than or equal),
// to be considered that the brew has actually started and
// to avoid trying to stop, when the seconds left are still basically, zero...
//
// it can't be very low or zero, because it causes the brew to stop almost immediatelly,
// since the seconds left, will most likely be zero at the very first second.
#define MIN_BREW_WEIGHT 9

class Mode_Brew : public Mode_Base
{
public:
    modes getMode();
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
    void tare(button_states button_state);
    void up(button_states button_state);
    void down(button_states button_state);
    void ok(button_states button_state);
    void cancel(button_states button_state);
    void coffee(button_states button_state);
};

#endif // MODE_BREW