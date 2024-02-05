#ifndef MODE_BREW
#define MODE_BREW
#include "modes/mode_base.h"
#include "modes/brew_stages.h"

class Mode_Brew : public Mode_Base
{
public:
    void setup();
    void loop();
    void render();
    void setStage(brew_stages stage);
    brew_stages stage;
    unsigned long brewStartTime;
    unsigned int brewSeconds;
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