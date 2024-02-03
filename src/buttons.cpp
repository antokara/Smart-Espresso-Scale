#include <Arduino.h>
#include "buttons.h"
#include "scale.h"
#include "lcd.h"
#include "device.h"
#include "modes/modes.h"
#include "modes/modes_controller.h"

/**
 * @author Antonios Karagiannis (antokarag@gmail.com)
 * @brief buttons controller
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief the state of the button:
 *        0: not pressed
 *        1: currently down/pressed and first loop
 *        2: currently down/pressed and consecutive loop
 */
byte Buttons::tare = 0;
byte Buttons::up = 0;
byte Buttons::down = 0;
byte Buttons::ok = 0;
byte Buttons::cancel = 0;
byte Buttons::coffee = 0;

/**
 * @brief should be called once, from the main setup() function
 *
 */
void Buttons::setup()
{
#ifdef SERIAL_DEBUG
  Serial.begin(9600);
  delay(500); // Give the serial terminal a chance to connect, if present
  Serial.print("Buttons::Setup()");
#endif

  pinMode(TARE_BUTTON_PIN, INPUT);
  pinMode(UP_BUTTON_PIN, INPUT);
  pinMode(DOWN_BUTTON_PIN, INPUT);
  pinMode(OK_BUTTON_PIN, INPUT);
  pinMode(CANCEL_BUTTON_PIN, INPUT);
  pinMode(COFFEE_BUTTON_PIN, INPUT);
}

/**
 * @brief should be called on every iteration of the main loop() function
 *
 */
void Buttons::loop()
{
  // check the buttons
  if (digitalRead(TARE_BUTTON_PIN) == HIGH)
  {
    if (Buttons::tare == 0)
    {
      Buttons::tare = 1;
    }
    else if (Buttons::tare == 1)
    {
      Buttons::tare == 2;
    }
  }
  else
  {
    Buttons::tare = 0;
  }

  if (digitalRead(UP_BUTTON_PIN) == HIGH)
  {
    if (Buttons::up == 0)
    {
      Buttons::up = 1;
    }
    else if (Buttons::up == 1)
    {
      Buttons::up == 2;
    }
  }
  else
  {
    Buttons::up = 0;
  }

  if (digitalRead(DOWN_BUTTON_PIN) == HIGH)
  {
    if (Buttons::down == 0)
    {
      Buttons::down = 1;
    }
    else if (Buttons::down == 1)
    {
      Buttons::down == 2;
    }
  }
  else
  {
    Buttons::down = 0;
  }

  if (digitalRead(OK_BUTTON_PIN) == HIGH)
  {
    if (Buttons::ok == 0)
    {
      Buttons::ok = 1;
    }
    else if (Buttons::ok == 1)
    {
      Buttons::ok == 2;
    }
  }
  else
  {
    Buttons::ok = 0;
  }

  if (digitalRead(CANCEL_BUTTON_PIN) == HIGH)
  {
    if (Buttons::cancel == 0)
    {
      Buttons::cancel = 1;
    }
    else if (Buttons::cancel == 1)
    {
      Buttons::cancel == 2;
    }
  }
  else
  {
    Buttons::cancel = 0;
  }

  if (digitalRead(COFFEE_BUTTON_PIN) == HIGH)
  {
    if (Buttons::coffee == 0)
    {
      Buttons::coffee = 1;
    }
    else if (Buttons::coffee == 1)
    {
      Buttons::coffee == 2;
    }
  }
  else
  {
    Buttons::coffee = 0;
  }
}