#ifndef LCD
#define LCD
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// the I2C address of the LCD display (hard coded usually)
#define LCD_I2C_ADDRESS 0x27

// I2C pins
#define LCD_SDA_PIN D0
#define LCD_SCL_PIN D1

class Lcd
{
public:
    // methods
    static void setup();
    static void loop();
};

#endif // LCD