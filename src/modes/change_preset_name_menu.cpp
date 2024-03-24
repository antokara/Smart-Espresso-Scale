#include "modes/change_preset_name_menu.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"

modes Mode_Change_Preset_Name_Menu::getMode()
{
    return modes_changePresetNameMenu;
}

void Mode_Change_Preset_Name_Menu::setup()
{
    Lcd::print("change name", 0, 0, clearLcd_all);
    Lcd::print(MENU_NAVIGATION, 0, 1);
};

void Mode_Change_Preset_Name_Menu::loop(){};

void Mode_Change_Preset_Name_Menu::tare()
{
    // NOP
}

void Mode_Change_Preset_Name_Menu::up()
{
    // TODO:
}

void Mode_Change_Preset_Name_Menu::down()
{
    Modes_Controller::setMode(modes_coffeeWeightMenu);
}

void Mode_Change_Preset_Name_Menu::ok()
{
    Modes_Controller::setMode(modes_changePresetName);
}

void Mode_Change_Preset_Name_Menu::cancel()
{
    Modes_Controller::setMode(modes_configurePreset);
}

void Mode_Change_Preset_Name_Menu::coffee()
{
    // NOP
}
