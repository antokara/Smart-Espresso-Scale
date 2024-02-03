#include <Arduino.h>
#include "services/device.h"
#include "services/buttons.h"
#include "services/lcd.h"
#include "modes/modes.h"
#include "modes/mode_scale.h"
#include "modes/mode_tare.h"
#include "modes/mode_selectPreset.h"
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
 * @brief our mode scale
 *
 */
Mode_Scale Modes_Controller::modeScale = Mode_Scale();
Mode_Tare Modes_Controller::modeTare = Mode_Tare();
Mode_SelectPreset Modes_Controller::modeSelectPreset = Mode_SelectPreset();
Mode_Base *Modes_Controller::currentMode;

void Modes_Controller::setup(){

};

void Modes_Controller::loop()
{
    // at the very start, handle mode changes (to also apply on the very first run...)
    if (Modes_Controller::mode != Modes_Controller::prevMode)
    {
        Serial.print("new mode");
        Serial.println(Modes_Controller::mode);
        Modes_Controller::prevMode = Modes_Controller::mode;
        Buttons::ignoreAll();
        switch (Modes_Controller::mode)
        {
        default:
        case modes_scale:
            Modes_Controller::currentMode = &Modes_Controller::modeScale;
            break;
        case modes_tare:
            Modes_Controller::currentMode = &Modes_Controller::modeTare;
            break;
        case modes_selectPreset:
            Modes_Controller::currentMode = &Modes_Controller::modeSelectPreset;
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