#ifndef MODE_START_TIMER
#define MODE_START_TIMER
#include "modes/base.h"
#include "services/presets/start_timers.h"

class Mode_Start_Timer : public Mode_Base
{
public:
    modes getMode();
    void setup();
    void loop();
    void render();

    start_timers startTimer;

    // user actions
    void tare(button_states button_state);
    void up(button_states button_state);
    void down(button_states button_state);
    void ok(button_states button_state);
    void cancel(button_states button_state);
    void coffee(button_states button_state);
};

#endif // #define MODE_START_TIMER
