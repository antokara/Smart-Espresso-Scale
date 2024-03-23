#ifndef MODE_TARE
#define MODE_TARE
#include "modes/base.h"

class Mode_Tare : public Mode_Base
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

#endif // MODE_TARE