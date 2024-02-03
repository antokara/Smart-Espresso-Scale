#ifndef MODE_SCALE
#define MODE_SCALE
#include "modes/mode_base.h"

class Mode_Scale : public Mode_Base
{
public:
    void setup();
    void loop();

    // user actions
    void tare();
    void up();
    void down();
    void ok();
    void cancel();
    void coffee();
};

#endif // MODE_SCALE