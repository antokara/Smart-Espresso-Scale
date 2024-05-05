#ifndef BUTTONS
#define BUTTONS
#include "services/button_states.h"

/**
 * @brief tare button pin.
 * D0-D28 which equates to GP0-GP28.
 *
 */
#define TARE_BUTTON_PIN D17

/**
 * @brief up button pin
 */
#define UP_BUTTON_PIN D18

/**
 * @brief down button pin
 */
#define DOWN_BUTTON_PIN D19

/**
 * @brief OK button pin
 */
#define OK_BUTTON_PIN D20

/**
 * @brief cancel button pin
 */
#define CANCEL_BUTTON_PIN D21

/**
 * @brief coffee button pin
 *
 */
#define COFFEE_BUTTON_PIN D22

class Buttons
{
public:
    // properties
    static button_states tare;
    static unsigned long tare_pressed_duration;
    static unsigned long tare_pressed_time;

    static button_states up;
    static unsigned long up_pressed_duration;
    static unsigned long up_pressed_time;

    static button_states down;
    static unsigned long down_pressed_duration;
    static unsigned long down_pressed_time;

    static button_states ok;
    static unsigned long ok_pressed_duration;
    static unsigned long ok_pressed_time;

    static button_states cancel;
    static unsigned long cancel_pressed_duration;
    static unsigned long cancel_pressed_time;

    static button_states coffee;
    static unsigned long coffee_pressed_duration;
    static unsigned long coffee_pressed_time;

    // methods
    static void setup();
    static void loop();
    static void ignoreAll();
};

#endif // BUTTONS