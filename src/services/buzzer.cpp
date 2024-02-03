#include "services/buzzer.h"
#include "services/device.h"

/**
 * @author Antonios Karagiannis (antokarag@gmail.com)
 * @brief Buzzer
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief turns on the buzzer
 *
 * This function is non-blocking, which means that even if you provide the duration parameter
 * the sketch execution will continue immediately even if the tone hasn’t finished playing.
 * @param frequency optional frequency (in Hertz), of the tone
 * @param duration optional duration of the tone (in milliseconds), 0 means never ending
 */
void Buzzer::on(unsigned int frequency, unsigned long duration)
{
    tone(BUZZER_PIN, frequency, duration);
}

/**
 * @brief turns off the buzzer
 *
 */
void Buzzer::off()
{
    noTone(BUZZER_PIN);
}

/**
 * @brief should be called once, from the main setup() function
 *
 */
void Buzzer::setup()
{
    pinMode(BUZZER_PIN, OUTPUT);
}

/**
 * @brief should be called on every iteration of the main loop() function
 *
 */
void Buzzer::loop()
{
}
