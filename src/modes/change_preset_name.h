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
    void tare(button_states button_state);
    void up(button_states button_state);
    void down(button_states button_state);
    void ok(button_states button_state);
    void cancel(button_states button_state);
    void coffee(button_states button_state);

private:
    static const char stopCharacter = '|';
    static const byte maxCharacters = 16;
    static String name;
    static byte characterIndex;
    static String characters;
};

#endif // #define MODE_CHANGE_PRESET_NAME
