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
    static button_states up;
    static button_states down;
    static button_states ok;
    static button_states cancel;
    static button_states coffee;

    // methods
    static void setup();
    static void loop();
    static void ignoreAll();
};

#endif // BUTTONS