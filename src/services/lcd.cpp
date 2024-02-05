#include "services/lcd.h"
#include "services/device.h"

// set the LCD address to 0x27 for a 16 chars and 2 line display
// the first parameter is  the I2C address
// the second parameter is how many rows are on your screen
// the  third parameter is how many columns are on your screen
LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS, 20, 4);

/**
 * @author Antonios Karagiannis (antokarag@gmail.com)
 * @brief LCD (display)
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief prints the text to the screen col/row given and optionally,
 * clears the screen before it prints.
 *
 * @param text what to print
 * @param col column (0 based)
 * @param row row (0 based)
 * @param clear nothing, all the screen or just the row
 */
void Lcd::print(String text, uint8_t col, uint8_t row, clearLcd clear)
{
    if (clear == clearLcd_all)
    {
        Lcd::clear();
    }
    else if (clear == clearLcd_row)
    {
        lcd.setCursor(0, row);
        String spaces = "";
        for (int i = 0; i < LCD_COLS; i++)
        {
            spaces += " ";
        }
        lcd.print(spaces);
    }
    lcd.setCursor(col, row);
    lcd.print(text);
}

/**
 * @brief clears the screen
 *
 */
void Lcd::clear()
{
    lcd.clear();
}

/**
 * @brief should be called once, from the main setup() function
 *
 */
void Lcd::setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    // initialize the lcd
    Wire.setSDA(LCD_SDA_PIN);
    Wire.setSCL(LCD_SCL_PIN);
    Wire.begin();
    lcd.init();
    lcd.backlight();
    digitalWrite(LED_BUILTIN, HIGH);
}

/**
 * @brief should be called on every iteration of the main loop() function
 *
 */
void Lcd::loop()
{
}
