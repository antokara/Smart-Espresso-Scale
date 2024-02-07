#ifndef MODE_SCALE
#define MODE_SCALE
#include <Arduino.h>
#include "modes/mode_base.h"

class Mode_Scale : public Mode_Base
{
public:
    void setup();
    void loop();
    unsigned long lastRender;
    String bufferedRender;

    // user actions
    void tare();
    void up();
    void down();
    void ok();
    void cancel();
    void coffee();
};

#endif // MODE_SCALE