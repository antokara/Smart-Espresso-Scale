#ifndef SCALE
#define SCALE
#include <Arduino.h>
#include <Wire.h>
#include "SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h"

// I2C pins
#define SCALE_SDA_PIN D2
#define SCALE_SCL_PIN D3

// we can increase I2C clock speed to 400kHz, the NAU7802 supports it
#define SCALE_I2C_CLOCK_HZ 400000

class Scale
{
public:
    // methods
    static void setup();
    static void loop();
};

#endif // SCALE