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
    // TODO: add timeout when no button has been pressed for 1 minute and start beeping. maybe add scene?
    if (Buttons::tare == 1)
    {
        Modes_Controller::mode = tare;
    }
    else if (Buttons::up == 1)
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
    else if (Buttons::coffee == 1)
    {
        Lcd::print("coffee", 0, 1);
    }

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