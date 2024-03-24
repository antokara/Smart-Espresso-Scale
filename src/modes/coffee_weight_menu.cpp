#include "modes/coffee_weight_menu.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"

modes Mode_Coffee_Weight_Menu::getMode()
{
    return modes_coffeeWeightMenu;
}

void Mode_Coffee_Weight_Menu::setup()
{
    Lcd::print("coffee weight", 0, 0, clearLcd_all);
    Lcd::print(MENU_NAVIGATION, 0, 1);
};

void Mode_Coffee_Weight_Menu::loop(){};

void Mode_Coffee_Weight_Menu::tare()
{
    // NOP
}

void Mode_Coffee_Weight_Menu::up()
{
    Modes_Controller::setMode(modes_changePresetNameMenu);
}

void Mode_Coffee_Weight_Menu::down()
{
    // TODO:
}

void Mode_Coffee_Weight_Menu::ok()
{
    Modes_Controller::setMode(modes_coffeeWeight);
}

void Mode_Coffee_Weight_Menu::cancel()
{
    Modes_Controller::setMode(modes_configurePreset);
}

void Mode_Coffee_Weight_Menu::coffee()
{
    // NOP
}
