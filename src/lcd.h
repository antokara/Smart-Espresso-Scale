#ifndef LCD
#define LCD
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class Lcd
{
public:
    // methods
    static void setup();
    static void loop();
};

#endif // LCD