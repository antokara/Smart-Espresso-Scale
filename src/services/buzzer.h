#ifndef BUZZER
#define BUZZER
#include <Arduino.h>

/**
 * @brief buzzer (positive) pin.
 * D0-D28 which equates to GP0-GP28.
 */
#define BUZZER_PIN D16

/**
 * @brief the default frequency (in Hertz) of the tone of the buzzer
 *
 * @see https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
 */
#define BUZZER_FREQUENCY_HZ 1000

/**
 * @brief the default duration of the tone in milliseconds
 *
 * 0 means until turned off
 *
 * @see https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
 */
#define BUZZER_DURATION_MS 0

class Buzzer
{
public:
    // methods
    static void setup();
    static void loop();
    static void on(unsigned int frequency = BUZZER_FREQUENCY_HZ, unsigned long duration = BUZZER_DURATION_MS);
    static void off();
};

#endif // BUZZER