#ifndef POWER
#define POWER
#include <Arduino.h>

/**
 * @brief fast off pin (immediate power off when LOW)
 * D0-D28 which equates to GP0-GP28.
 */
#define POWER_FAST_OFF_PIN D15

/**
 * @brief power sense/control pin
 *  HIGH when unpressed
 *  LOW when pressed
 */
#define POWER_SENSE_CTL_PIN D14

/**
 * @brief time to power off when idle
 *
 */
#define POWER_IDLE_OFF_SECONDS 60

/**
 * @brief milliseconds for the power off button to need to be pressed
 *        in order to power off the device
 */
#define POWER_OFF_BUTTON_MILLIS 350

class Power
{
public:
    // methods
    static void setup();
    static void loop();
    static void trackActivity();
    static void checkActivity();
    static void powerOff();

    // props
    static unsigned long idleSinceTime;
    static unsigned long powerOffPressTime;
    static bool isPoweringOff;
};

#endif // POWER