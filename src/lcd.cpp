#include <lcd.h>
#include <device.h>

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

void Lcd::print(String text, uint8_t col, uint8_t row)
{
    lcd.setCursor(col, row);
    lcd.print(text);
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
    // lcd.setCursor(0, 0);
    // lcd.print("Hello, world!");
    // lcd.setCursor(0, 1);
    // lcd.print("Testing 2nd row");
    digitalWrite(LED_BUILTIN, HIGH);
}

/**
 * @brief should be called on every iteration of the main loop() function
 *
 */
void Lcd::loop()
{
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(1000);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(1000);
}
