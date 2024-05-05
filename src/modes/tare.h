#ifndef MODE_TARE
#define MODE_TARE
#include "modes/base.h"

class Mode_Tare : public Mode_Base
{
public:
    modes getMode();
    void setup();
    void loop();

    // user actions
    void tare(button_states button_state);
    void up(button_states button_state);
    void down(button_states button_state);
    void ok(button_states button_state);
    void cancel(button_states button_state);
    void coffee(button_states button_state);
};

#endif // MODE_TARE