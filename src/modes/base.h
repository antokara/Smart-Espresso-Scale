#ifndef MODE_BASE
#define MODE_BASE
#include <Arduino.h>
#include "services/lcd.h"
#include "modes/enums/modes.h"
#include "services/button_states.h"

/**
 * @brief the menu navigation text
 * to display on the 2nd row of the LCD screen
 */
#define MENU_NAVIGATION "up/dn/ok/back"

class Mode_Base
{
public:
    // standard methods (must be implemented by the derived class)
    virtual void setup() = 0;
    virtual void loop() = 0;
    virtual modes getMode() = 0;

    // LCD render debouncer
    unsigned long lastRenderTime;
    String bufferedRenderText;
    uint8_t bufferedRenderCol;
    uint8_t bufferedRenderRow;
    clearLcd bufferedRenderClear;
    void tryRenderNow(String text, uint8_t col, uint8_t row, clearLcd clear = clearLcd_none);
    void tryRenderBuffered();
    bool hasRenderBuffered();
    void clearBufferedRender();

    /**
     * @brief user actions
     *
     * these are abstract and must be implemented by the derived class
     * even for NOOP, to ensure we did not forget to handle a user action
     *
     */
    virtual void tare(button_states button_state) = 0;
    virtual void up(button_states button_state) = 0;
    virtual void down(button_states button_state) = 0;
    virtual void ok(button_states button_state) = 0;
    virtual void cancel(button_states button_state) = 0;
    virtual void coffee(button_states button_state) = 0;
};

#endif // MODE_BASE