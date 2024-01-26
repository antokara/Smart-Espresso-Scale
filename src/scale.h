#ifndef SCALE
#define SCALE
#include <Arduino.h>
#include <Wire.h>
#include "SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h"

class Scale
{
public:
    // methods
    static void setup();
    static void loop();
};

#endif // SCALE