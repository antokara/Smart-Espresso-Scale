#ifndef LCD
#define LCD
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// milliseconds that pixels take to turn off
// anything less than, can create ghosting
#define LCD_REFRESH_RATE 500

// the I2C address of the LCD display (hard coded usually)
#define LCD_I2C_ADDRESS 0x27

// I2C pins (D0-D16 which equate to GP0-GP16)
#define LCD_SDA_PIN D0
#define LCD_SCL_PIN D1

// count of rows and columns
#define LCD_ROWS 2
#define LCD_COLS 16

enum clearLcd
{
    clearLcd_none,
    clearLcd_all,
    clearLcd_row
};

class Lcd
{
public:
    // methods
    static void setup();
    static void loop();
    static void print(String text, uint8_t col, uint8_t row, clearLcd clear = clearLcd_none);
    static void clear();
    static void blink(uint8_t col, uint8_t row);
    static void noBlink();
};

#endif // LCD