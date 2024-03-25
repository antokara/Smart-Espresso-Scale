#include "modes/coffee_weight.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"
#include "services/scale.h"

// TODO: change dynamically depending on press duration
float Mode_Coffee_Weight::coffee_weight_step = 0.1;
float Mode_Coffee_Weight::coffee_weight;

modes Mode_Coffee_Weight::getMode()
{
    return modes_coffeeWeight;
}

void Mode_Coffee_Weight::setup()
{
    Lcd::print("coffee weight", 0, 0, clearLcd_all);
    Mode_Coffee_Weight::coffee_weight = Presets::getPreset()->coffeeWeight;
    Mode_Coffee_Weight::render();
};

void Mode_Coffee_Weight::loop(){};

void Mode_Coffee_Weight::render()
{
    Lcd::print(String(Mode_Coffee_Weight::coffee_weight) + SCALE_UNIT_SUFFIX_GRAMS, 0, 1);
};

void Mode_Coffee_Weight::tare()
{
    // NOP
}

void Mode_Coffee_Weight::up()
{
    if (Mode_Coffee_Weight::coffee_weight + Mode_Coffee_Weight::coffee_weight_step < MAX_COFFEE_WEIGHT)
    {
        Mode_Coffee_Weight::coffee_weight += Mode_Coffee_Weight::coffee_weight_step;
        Mode_Coffee_Weight::render();
    }
}

void Mode_Coffee_Weight::down()
{
    if (Mode_Coffee_Weight::coffee_weight - Mode_Coffee_Weight::coffee_weight_step > MIN_COFFEE_WEIGHT)
    {
        Mode_Coffee_Weight::coffee_weight -= Mode_Coffee_Weight::coffee_weight_step;
        Mode_Coffee_Weight::render();
    }
}

void Mode_Coffee_Weight::ok()
{
    // TODO:
    Presets::getPreset()->coffeeWeight = Mode_Coffee_Weight::coffee_weight;
    Presets::save();
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
