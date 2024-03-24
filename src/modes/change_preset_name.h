#ifndef MODE_CHANGE_PRESET_NAME
#define MODE_CHANGE_PRESET_NAME
#include "modes/base.h"

class Mode_Change_Preset_Name : public Mode_Base
{
public:
    modes getMode();
    void setup();
    void loop();
    void render();

    // user actions
    void tare();
    void up();
    void down();
    void ok();
    void cancel();
    void coffee();

private:
    static const char stopCharacter = '|';
    static const byte maxCharacters = 16;
    static String name;
    static byte characterIndex;
    static String characters;
};

#endif // #define MODE_CHANGE_PRESET_NAME
