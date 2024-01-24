#include <lcd.h>

/**
 * @author Antonios Karagiannis (antokarag@gmail.com)
 * @brief LCD (display)
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */
/**
 * @brief should be called once, from the main setup() function
 *
 */
void Lcd::setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * @brief should be called on every iteration of the main loop() function
 *
 */
void Lcd::loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}