#include "modes/coffee_weight.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"
#include "services/scale.h"

modes Mode_Coffee_Weight::getMode()
{
    return modes_coffeeWeightMenu;
}

void Mode_Coffee_Weight::setup()
{
    Lcd::print("coffee weight", 0, 0, clearLcd_all);
    Lcd::print(String(Presets::getPreset()->coffeeWeight) + SCALE_UNIT_SUFFIX_GRAMS, 0, 1);
};

void Mode_Coffee_Weight::loop(){};

void Mode_Coffee_Weight::tare()
{
    // NOP
}

void Mode_Coffee_Weight::up()
{
}

void Mode_Coffee_Weight::down()
{
    // TODO:
}

void Mode_Coffee_Weight::ok()
{
    // TODO:
    Modes_Controller::setMode(this->_okMode);
}

void Mode_Coffee_Weight::cancel()
{
    Modes_Controller::setMode(this->_parentMode);
}

void Mode_Coffee_Weight::coffee()
{
    // NOP
}
