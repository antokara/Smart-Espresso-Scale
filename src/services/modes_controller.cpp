#include <Arduino.h>
#include "services/device.h"
#include "services/buttons.h"
#include "services/lcd.h"
#include "modes/enums/modes.h"
#include "modes/scale.h"
#include "modes/tare.h"
#include "modes/select_preset.h"
#include "modes/brew.h"
#include "services/modes_controller.h"

/**
 * @brief the active mode
 *
 */
modes Modes_Controller::mode = modes_scale;

/**
 * @brief the previously active mode
 *
 */
modes Modes_Controller::prevMode;

/**
 * @brief the current mode instance
 *
 */
Mode_Base *Modes_Controller::currentMode;

/**
 * @brief sets the new mode.
 *
 * important: the new mode does not take effect immediatelly.
 *            rather, the timing of that event, gets handled properly
 *            inside the loop method of this class.
 *            this method helps us control the change from a single approved method.
 *
 * @param newMode
 * @see loop()
 */
void Modes_Controller::setMode(modes newMode)
{
    if (Modes_Controller::mode != newMode)
    {
        Modes_Controller::mode = newMode;
    }
}

void Modes_Controller::setup(){

};

void Modes_Controller::loop()
{
    // handle mode changes, as the first thing we do (so that don't have NULL, on the first loop)
    if (Modes_Controller::mode != Modes_Controller::prevMode)
    {
        Modes_Controller::prevMode = Modes_Controller::mode;
        delete Modes_Controller::currentMode;
        Buttons::ignoreAll();
        switch (Modes_Controller::mode)
        {
        default:
        case modes_scale:
            Modes_Controller::currentMode = new Mode_Scale();
            break;
        case modes_tare:
            Modes_Controller::currentMode = new Mode_Tare();
            break;
        case modes_selectPreset:
            Modes_Controller::currentMode = new Mode_Select_Preset();
            break;
        case modes_brew:
            Modes_Controller::currentMode = new Mode_Brew();
            break;
        }
        Modes_Controller::currentMode->setup();
    }

    // run the mode's loop
    Modes_Controller::currentMode->loop();

    // TODO: add timeout when no button has been pressed for 1 minute
    //       and start beeping. maybe add scene? OR implement auto shut-off

    // check for user actions (buttons)
    if (Buttons::tare == button_pressed)
    {
        Modes_Controller::currentMode->tare();
    }
    else if (Buttons::up == button_pressed)
    {
        Modes_Controller::currentMode->up();
    }
    else if (Buttons::down == button_pressed)
    {
        Modes_Controller::currentMode->down();
    }
    else if (Buttons::ok == button_pressed)
    {
        Modes_Controller::currentMode->ok();
    }
    else if (Buttons::cancel == button_pressed)
    {
        Modes_Controller::currentMode->cancel();
    }
    else if (Buttons::coffee == button_pressed)
    {
        Modes_Controller::currentMode->coffee();
    }
};