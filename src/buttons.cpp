#include <Arduino.h>
#include "buttons.h"
#include "scale.h"
#include "lcd.h"
#include "device.h"

/**
 * @author Antonios Karagiannis (antokarag@gmail.com)
 * @brief buttons controller
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief if the tare button is pressed
 *
 */
bool Buttons::isTarePressed = false;

/**
 * @brief if the up button is pressed
 *
 */
bool Buttons::isUpPressed = false;

/**
 * @brief if the down button is pressed
 *
 */
bool Buttons::isDownPressed = false;

/**
 * @brief if the ok button is pressed
 *
 */
bool Buttons::isOkPressed = false;

/**
 * @brief if the cancel button is pressed
 *
 */
bool Buttons::isCancelPressed = false;

/**
 * @brief if the coffee button is pressed
 *
 */
bool Buttons::isCoffeePressed = false;

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
  if (digitalRead(TARE_BUTTON_PIN) == HIGH && Buttons::isTarePressed == false)
  {
    Buttons::isTarePressed = true;
    // TODO: move to mode
    Scale::tare();
  }
  else
  {
    Buttons::isTarePressed = false;
  }

  if (digitalRead(UP_BUTTON_PIN) == HIGH && Buttons::isUpPressed == false)
  {
    Buttons::isUpPressed = true;
    Lcd::print("up    ", 0, 1);
  }
  else
  {
    Buttons::isUpPressed = false;
  }

  if (digitalRead(DOWN_BUTTON_PIN) == HIGH && Buttons::isDownPressed == false)
  {
    Buttons::isDownPressed = true;
    Lcd::print("down  ", 0, 1);
  }
  else
  {
    Buttons::isDownPressed = false;
  }

  if (digitalRead(OK_BUTTON_PIN) == HIGH && Buttons::isOkPressed == false)
  {
    Buttons::isOkPressed = true;
    Lcd::print("ok    ", 0, 1);
  }
  else
  {
    Buttons::isOkPressed = false;
  }

  if (digitalRead(CANCEL_BUTTON_PIN) == HIGH && Buttons::isCancelPressed == false)
  {
    Buttons::isCancelPressed = true;
    Lcd::print("cancel", 0, 1);
  }
  else
  {
    Buttons::isCancelPressed = false;
  }

  if (digitalRead(COFFEE_BUTTON_PIN) == HIGH && Buttons::isCoffeePressed == false)
  {
    Buttons::isCoffeePressed = true;
    Lcd::print("coffee", 0, 1);
  }
  else
  {
    Buttons::isCoffeePressed = false;
  }
}