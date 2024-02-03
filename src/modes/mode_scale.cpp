#include <modes/mode_scale.h>

void Mode_Scale::setup(){

};

void Mode_Scale::loop()
{
    if (Scale::hasWeightChanged)
    {
        // TODO: debounce the screen updates because the LCD has a very slow refresh rate
        //       the last value, must be retained/shown eventually...
        Lcd::print(Scale::formatWeight(Scale::getWeight()), 0, 0);
    }
};
