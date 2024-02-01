#ifndef BUTTONS
#define BUTTONS

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
    static bool isTarePressed;
    static bool isUpPressed;
    static bool isDownPressed;
    static bool isOkPressed;
    static bool isCancelPressed;
    static bool isCoffeePressed;

    // methods
    static void setup();
    static void loop();
};

#endif // BUTTONS