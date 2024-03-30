#ifndef MODE_STOP_TIMER
#define MODE_STOP_TIMER
#include "modes/base.h"
#include "services/presets/stop_timers.h"

class Mode_Stop_Timer : public Mode_Base
{
public:
    modes getMode();
    void setup();
    void loop();
    void render();

    stop_timers stopTimer;

    // user actions
    void tare(button_states button_state);
    void up(button_states button_state);
    void down(button_states button_state);
    void ok(button_states button_state);
    void cancel(button_states button_state);
    void coffee(button_states button_state);
};

#endif // #define MODE_STOP_TIMER
