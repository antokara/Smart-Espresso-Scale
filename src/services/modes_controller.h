#ifndef MODES_CONTROLLER
#define MODES_CONTROLLER
#include "modes/enums/modes.h"
#include "modes/base.h"
#include "modes/scale.h"
#include "modes/tare.h"
#include "modes/selectPreset.h"

/**
 * @brief this class is responsible for:
 *  - handling the mode switching
 *  - creating/destroying modes if needed
 *  - executing the setup/loop of the current mode
 *  - delegating events (e.g. user button presses) to the current mode
 */
class Modes_Controller
{
private:
    // properties
    static modes mode;
    static modes prevMode;
    static Mode_Base *currentMode;

public:
    // methods
    static void setup();
    static void loop();
    static void setMode(modes newMode);
};

#endif // MODES_CONTROLLER