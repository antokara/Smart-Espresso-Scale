#include "modes/change_preset_name.h"
#include "modes/configure_preset.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"
#include "services/lcd.h"

String Mode_Change_Preset_Name::name;
char Mode_Change_Preset_Name::character;

modes Mode_Change_Preset_Name::getMode()
{
    return modes_changePresetName;
}

void Mode_Change_Preset_Name::setup()
{
    Mode_Change_Preset_Name::character = '_';
    Lcd::print("enter new name", 0, 0, clearLcd_all);
    Mode_Change_Preset_Name::render();
};

void Mode_Change_Preset_Name::loop(){};

void Mode_Change_Preset_Name::render()
{
    Lcd::print(Mode_Change_Preset_Name::name, 0, 1);
    Lcd::print(String(Mode_Change_Preset_Name::character), Mode_Change_Preset_Name::name.length(), 1);
};

void Mode_Change_Preset_Name::tare()
{
    // NOP
}

void Mode_Change_Preset_Name::up()
{
}

void Mode_Change_Preset_Name::down()
{
}

void Mode_Change_Preset_Name::ok()
{
}

void Mode_Change_Preset_Name::cancel()
{
    Modes_Controller::setMode(modes_changePresetNameMenu);
}

void Mode_Change_Preset_Name::coffee()
{
    // NOP
}
