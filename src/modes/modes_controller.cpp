#include <modes/modes.h>
#include <modes/modes_controller.h>

/**
 * @brief the active mode
 *
 */
modes Modes_Controller::mode = scale;

/**
 * @brief our mode scale
 *
 */
Mode_Scale Modes_Controller::modeScale = Mode_Scale();

Mode_Tare Modes_Controller::modeTare = Mode_Tare();

void Modes_Controller::setup(){};

void Modes_Controller::loop()
{
    // TODO: consider adding a setup call, upon mode switch;
    switch (Modes_Controller::mode)
    {
    default:
    case scale:
        Modes_Controller::modeScale.loop();
        break;
    case tare:
        Modes_Controller::modeTare.loop();
        break;
    }
};