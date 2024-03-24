#include "modes/change_preset_name.h"
#include "modes/configure_preset.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"
#include "services/lcd.h"

String Mode_Change_Preset_Name::name;
String Mode_Change_Preset_Name::characters = "abcdefghijklmnopqrstuvwxyz ." + String(Mode_Change_Preset_Name::stopCharacter);
byte Mode_Change_Preset_Name::characterIndex;

modes Mode_Change_Preset_Name::getMode()
{
    return modes_changePresetName;
}

void Mode_Change_Preset_Name::setup()
{
    Mode_Change_Preset_Name::name = "";
    Mode_Change_Preset_Name::characterIndex = 0;
    Lcd::print("enter new name", 0, 0, clearLcd_all);
    Mode_Change_Preset_Name::render();
};

void Mode_Change_Preset_Name::loop(){};

void Mode_Change_Preset_Name::render()
{
    Lcd::print(Mode_Change_Preset_Name::name, 0, 1);
    Lcd::print(String(Mode_Change_Preset_Name::characters.charAt(Mode_Change_Preset_Name::characterIndex)), Mode_Change_Preset_Name::name.length(), 1);
    Lcd::blink(Mode_Change_Preset_Name::name.length(), 1);
};

void Mode_Change_Preset_Name::tare()
{
    // NOP
}

void Mode_Change_Preset_Name::up()
{

    if (Mode_Change_Preset_Name::characterIndex > 0)
    {
        Mode_Change_Preset_Name::characterIndex--;
    }
    else
    {
        Mode_Change_Preset_Name::characterIndex = Mode_Change_Preset_Name::characters.length() - 1;
    }
    Mode_Change_Preset_Name::render();
}

void Mode_Change_Preset_Name::down()
{
    if (Mode_Change_Preset_Name::characterIndex < Mode_Change_Preset_Name::characters.length() - 1)
    {
        Mode_Change_Preset_Name::characterIndex++;
    }
    else
    {
        Mode_Change_Preset_Name::characterIndex = 0;
    }
    Mode_Change_Preset_Name::render();
}

void Mode_Change_Preset_Name::ok()
{
    // when the max allowed chars is reached or the stop character is entered
    if (Mode_Change_Preset_Name::name.length() >= maxCharacters || Mode_Change_Preset_Name::characters.charAt(Mode_Change_Preset_Name::characterIndex) == Mode_Change_Preset_Name::stopCharacter)
    {
        // save and exit
        Lcd::noBlink();
        Presets::getPreset()->name = Mode_Change_Preset_Name::name;
        Presets::save();
        Modes_Controller::setMode(modes_changePresetNameMenu);
    }
    else
    {
        Mode_Change_Preset_Name::name += String(Mode_Change_Preset_Name::characters.charAt(Mode_Change_Preset_Name::characterIndex));
        Mode_Change_Preset_Name::characterIndex = 0;
        Mode_Change_Preset_Name::render();
    }
}

void Mode_Change_Preset_Name::cancel()
{
    Modes_Controller::setMode(modes_changePresetNameMenu);
    Lcd::noBlink();
}

void Mode_Change_Preset_Name::coffee()
{
    // NOP
}
