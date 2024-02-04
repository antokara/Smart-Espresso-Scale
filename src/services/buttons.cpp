#include <Arduino.h>
#include "services/buttons.h"
#include "services/scale.h"
#include "services/lcd.h"
#include "services/device.h"
#include "services/modes_controller.h"
#include "modes/modes.h"

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
 */
button_states Buttons::tare = button_up;
button_states Buttons::up = button_up;
button_states Buttons::down = button_up;
button_states Buttons::ok = button_up;
button_states Buttons::cancel = button_up;
button_states Buttons::coffee = button_up;

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
    if (Buttons::tare == button_up)
    {
      Buttons::tare = button_pressed;
    }
    else if (Buttons::tare == button_pressed)
    {
      Buttons::tare = button_down;
    }
  }
  else if (Buttons::tare != button_up)
  {
    Buttons::tare = button_up;
  }

  if (digitalRead(UP_BUTTON_PIN) == HIGH)
  {
    if (Buttons::up == button_up)
    {
      Buttons::up = button_pressed;
    }
    else if (Buttons::up == button_pressed)
    {
      Buttons::up = button_down;
    }
  }
  else if (Buttons::up != button_up)
  {
    Buttons::up = button_up;
  }

  if (digitalRead(DOWN_BUTTON_PIN) == HIGH)
  {
    if (Buttons::down == button_up)
    {
      Buttons::down = button_pressed;
    }
    else if (Buttons::down == button_pressed)
    {
      Buttons::down = button_down;
    }
  }
  else if (Buttons::down != button_up)
  {
    Buttons::down = button_up;
  }

  if (digitalRead(OK_BUTTON_PIN) == HIGH)
  {
    if (Buttons::ok == button_up)
    {
      Buttons::ok = button_pressed;
    }
    else if (Buttons::ok == button_pressed)
    {
      Buttons::ok = button_down;
    }
  }
  else if (Buttons::ok != button_up)
  {
    Buttons::ok = button_up;
  }

  if (digitalRead(CANCEL_BUTTON_PIN) == HIGH)
  {
    if (Buttons::cancel == button_up)
    {
      Buttons::cancel = button_pressed;
    }
    else if (Buttons::cancel == button_pressed)
    {
      Buttons::cancel = button_down;
    }
  }
  else if (Buttons::cancel != button_up)
  {
    Buttons::cancel = button_up;
  }

  if (digitalRead(COFFEE_BUTTON_PIN) == HIGH)
  {
    if (Buttons::coffee == button_up)
    {
      Buttons::coffee = button_pressed;
    }
    else if (Buttons::coffee == button_pressed)
    {
      Buttons::coffee = button_down;
    }
  }
  else if (Buttons::up != button_up)
  {
    Buttons::coffee = button_up;
  }
}

/**
 * @brief set all buttons to ignore state.
 *
 * This is needed after a navigation, to prevent
 * actions to be taken on a different menu
 * for a button that was will pressed (e.g. cancel).
 *
 * Sort of a debounce...
 */
void Buttons::ignoreAll()
{
  Buttons::tare = button_ignore;
  Buttons::up = button_ignore;
  Buttons::down = button_ignore;
  Buttons::ok = button_ignore;
  Buttons::cancel = button_ignore;
  Buttons::coffee = button_ignore;
}