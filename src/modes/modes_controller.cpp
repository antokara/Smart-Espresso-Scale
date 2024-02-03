#include <device.h>
#include <buttons.h>
#include <lcd.h>
#include <modes/modes.h>
#include <modes/mode_scale.h>
#include <modes/mode_tare.h>
#include <modes/mode_selectPreset.h>
#include <modes/modes_controller.h>

/**
 * @brief the active mode
 *
 */
modes Modes_Controller::mode = scale;

/**
 * @brief the previously active mode
 *
 */
modes Modes_Controller::prevMode = scale;

/**
 * @brief our mode scale
 *
 */
Mode_Scale Modes_Controller::modeScale = Mode_Scale();
Mode_Tare Modes_Controller::modeTare = Mode_Tare();
Mode_SelectPreset Modes_Controller::modeSelectPreset = Mode_SelectPreset();

void Modes_Controller::setup(){};

void Modes_Controller::loop()
{
    // TODO: add timeout when no button has been pressed for 1 minute and start beeping. maybe add scene?
    if (Buttons::up == 1)
    {
        Lcd::print("up    ", 0, 1);
    }
    else if (Buttons::down == 1)
    {
        Lcd::print("down   ", 0, 1);
    }
    else if (Buttons::ok == 1)
    {
        Lcd::print("ok   ", 0, 1);
    }
    else if (Buttons::cancel == 1)
    {
        Lcd::print("cancel", 0, 1);
    }

    if (Modes_Controller::mode != Modes_Controller::prevMode)
    {
        Modes_Controller::prevMode = Modes_Controller::mode;
        Buttons::ignoreAll();
        switch (Modes_Controller::mode)
        {
        default:
        case scale:
            Modes_Controller::modeScale.setup();
            break;
        case tare:
            Modes_Controller::modeTare.setup();
            break;
        case selectPreset:
            Modes_Controller::modeSelectPreset.setup();
            break;
        }
    }

    switch (Modes_Controller::mode)
    {
    default:
    case scale:
        Modes_Controller::modeScale.loop();
        break;
    case tare:
        Modes_Controller::modeTare.loop();
        break;
    case selectPreset:
        Modes_Controller::modeSelectPreset.loop();
        break;
    }
};