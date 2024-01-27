#include <Arduino.h>
#include "secrets.h"
#include "device.h"

/**
 * @author Antonios Karagiannis (antokarag@gmail.com)
 * @brief definitions for the Device
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief flag to keep track of the first loop
 */
bool Device::firstLoop = true;

/**
 * @brief should be called once, from the main setup() function
 *
 */
void Device::setup()
{
#ifdef SERIAL_DEBUG
  Serial.begin(9600);
  delay(500); // Give the serial terminal a chance to connect, if present
  Serial.print("Device::Setup()");
#endif
}

/**
 * @brief should be called on every iteration of the main loop() function
 *
 */
void Device::loop()
{
  /**
   * @brief only on the first loop,
   *        swap the status to force an update of the status sensor,
   *        in order to have a record of the time the device rebooted...
   *
   */
  if (Device::firstLoop)
  {
    Device::firstLoop = false;
  }
}