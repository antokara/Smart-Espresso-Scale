#include "services/power.h"
#include "services/device.h"

/**
 * @author Antonios Karagiannis (antokarag@gmail.com)
 * @brief Power Management
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief milliseconds since the last activity was tracked
 *
 */
unsigned long Power::idleSinceTime = 0;

/**
 * @brief milliseconds since the power off button was pressed
 *
 */
unsigned long Power::powerOffPressTime = 0;

/**
 * @brief if true, the system is currently powering off and the loop is exiting early...
 *
 */
bool Power::isPoweringOff = false;

/**
 * @brief updates the activity time to postpone the idle (auto power off)
 * TODO: call this from places
 */
void Power::trackActivity()
{
    Power::idleSinceTime = millis();
}

/**
 * @brief checks if the device is idle and needs to auto power off
 * must be called from within the loop
 */
void Power::checkActivity()
{
    // TODO:
}

/**
 * @brief powers off the system
 *
 */
void Power::powerOff()
{
    Power::isPoweringOff = true;
    digitalWrite(POWER_FAST_OFF_PIN, HIGH);
}

/**
 * @brief should be called once, from the main setup() function
 *
 */
void Power::setup()
{
    Power::trackActivity();
    pinMode(POWER_FAST_OFF_PIN, OUTPUT);
    digitalWrite(POWER_FAST_OFF_PIN, LOW);
    pinMode(POWER_SENSE_CTL_PIN, INPUT_PULLUP);
}

/**
 * @brief should be called on every iteration of the main loop() function
 *
 */
void Power::loop()
{
    // exit early if the system is powering off
    if (Power::isPoweringOff)
    {
        return;
    }

    if (digitalRead(POWER_SENSE_CTL_PIN) == LOW)
    {
        // button pressed
        if (Power::powerOffPressTime == 0)
        {
            Power::powerOffPressTime = millis();
        }
        else if (millis() - Power::powerOffPressTime >= POWER_OFF_BUTTON_MILLIS)
        {
            // previously pressed for long enough
            Power::powerOff();
        }
    }
    else
    {
        // button unpressed
        Power::powerOffPressTime = 0;
        Power::checkActivity();
    }
}
