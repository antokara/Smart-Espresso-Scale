#ifndef MODE_AUTO_PUMP
#define MODE_AUTO_PUMP
#include "modes/base.h"

class Mode_Auto_Pump : public Mode_Base
{
public:
    modes getMode();
    void setup();
    void loop();
    void render();

    bool autoPump;

    // user actions
    void tare(button_states button_state);
    void up(button_states button_state);
    void down(button_states button_state);
    void ok(button_states button_state);
    void cancel(button_states button_state);
    void coffee(button_states button_state);
};

#endif // #define MODE_AUTO_PUMP
