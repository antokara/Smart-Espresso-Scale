#include <Arduino.h>
#include "services/device.h"
#include "services/buttons.h"
#include "services/lcd.h"
#include "modes/enums/modes.h"
#include "modes/scale.h"
#include "modes/tare.h"
#include "modes/select_preset.h"
#include "modes/brew.h"
#include "modes/custom_brew_menu.h"
#include "modes/presets_menu.h"
#include "modes/configure_preset.h"
#include "modes/change_preset_name_menu.h"
#include "modes/change_preset_name.h"
#include "modes/coffee_weight_menu.h"
#include "services/modes_controller.h"

/**
 * @brief the current mode instance
 *
 */
Mode_Base *Modes_Controller::currentMode;

/**
 * @brief sets the new mode.
 *
 * @param newMode the new enum mode to set (using default parms)
 */
void Modes_Controller::setMode(modes newMode)
{
    if (Modes_Controller::currentMode == NULL || Modes_Controller::currentMode->getMode() != newMode)
    {
        switch (newMode)
        {
        default: // NOP
        case modes_scale:
            Modes_Controller::setMode(new Mode_Scale());
            break;
        case modes_tare:
            Modes_Controller::setMode(new Mode_Tare());
            break;
        case modes_selectPreset:
            Modes_Controller::setMode(new Mode_Select_Preset());
            break;
        case modes_brew:
            Modes_Controller::setMode(new Mode_Brew());
            break;
        case modes_customBrewMenu:
            Modes_Controller::setMode(new Mode_Custom_Brew_Menu());
            break;
        case modes_presetsMenu:
            Modes_Controller::setMode(new Mode_Presets_Menu());
            break;
        case modes_configurePreset:
            Modes_Controller::setMode(new Mode_Configure_Preset());
            break;
        case modes_changePresetNameMenu:
            Modes_Controller::setMode(new Mode_Change_Preset_Name_Menu());
            break;
        case modes_changePresetName:
            Modes_Controller::setMode(new Mode_Change_Preset_Name());
            break;
        case modes_coffeeWeightMenu:
            Modes_Controller::setMode(new Mode_Coffee_Weight_Menu());
            break;
        }
    }
}

/**
 * @brief sets the new mode.
 *
 * @param newMode the new mode instance to set (as provided)
 */
void Modes_Controller::setMode(Mode_Base *newMode)
{
    if (Modes_Controller::currentMode == NULL || Modes_Controller::currentMode->getMode() != newMode->getMode())
    {
        if (Modes_Controller::currentMode != NULL)
        {
            delete Modes_Controller::currentMode;
        }
        Buttons::ignoreAll();
        Modes_Controller::currentMode = newMode;
        Modes_Controller::currentMode->setup();
    }
}

void Modes_Controller::setup()
{
    // start with the scale mode...
    Modes_Controller::setMode(modes_scale);
};

void Modes_Controller::loop()
{
    // run the mode's loop
    Modes_Controller::currentMode->loop();

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