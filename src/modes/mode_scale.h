#ifndef MODE_SCALE
#define MODE_SCALE
#include <Arduino.h>
#include <modes/mode_base.h>

class Mode_Scale : public Mode_Base
{
public:
    void setup();
    void loop();
};

#endif // MODE_SCALE