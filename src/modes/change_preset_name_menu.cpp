#include "modes/change_preset_name_menu.h"
#include "modes/configure_preset.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"

void Mode_Change_Preset_Name_Menu::setup()
{
    Lcd::print("change name", 0, 0, clearLcd_all);
    Lcd::print(Presets::presets[Mode_Configure_Preset::selectedPresetIndex]->name, 0, 1);
};

void Mode_Change_Preset_Name_Menu::loop(){};

void Mode_Change_Preset_Name_Menu::tare()
{
    // NOP
}

void Mode_Change_Preset_Name_Menu::up()
{
}

void Mode_Change_Preset_Name_Menu::down()
{
}

void Mode_Change_Preset_Name_Menu::ok()
{
}

void Mode_Change_Preset_Name_Menu::cancel()
{
    Modes_Controller::setMode(modes_configurePreset);
}

void Mode_Change_Preset_Name_Menu::coffee()
{
    // NOP
}
