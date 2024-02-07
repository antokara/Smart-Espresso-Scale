#include "modes/mode_base.h"

/**
 * @brief attempts to render now, the text with the options provided and if it can't,
 * it buffers it for later. This should be called when new values (e.g. weight has changed)
 * need to be render immediatelly (if possible).
 *
 * this is a debouncer of some sort, to reduce LCD display ghosting,
 * from rapid renders on the same pixels.
 *
 * @param text
 * @param col
 * @param row
 * @param clear
 */
void Mode_Base::tryRenderNow(String text, uint8_t col, uint8_t row, clearLcd clear)
{
    if (millis() - Mode_Base::lastRenderTime > LCD_REFRESH_RATE)
    {
        Lcd::print(text, col, row, clear);
        Mode_Base::clearBufferedRender();
    }
    else
    {
        Mode_Base::bufferedRenderText = text;
        Mode_Base::bufferedRenderCol = col;
        Mode_Base::bufferedRenderRow = row;
        Mode_Base::bufferedRenderClear = clear;
    }
}

/**
 * @brief try to render buffered text (if any). This should be called when there are no new values
 * to render and we may want to render any previously buffered values that got debounced.
 *
 */
void Mode_Base::tryRenderBuffered()
{
    if (Mode_Base::bufferedRenderText != "" && millis() - Mode_Base::lastRenderTime > LCD_REFRESH_RATE)
    {
        Lcd::print(Mode_Base::bufferedRenderText, Mode_Base::bufferedRenderCol, Mode_Base::bufferedRenderRow, Mode_Base::bufferedRenderClear);
        Mode_Base::clearBufferedRender();
    }
}

/**
 * @brief clears any previously buffered render values and
 * resets the lastRenderTime
 *
 */
void Mode_Base::clearBufferedRender()
{
    Mode_Base::lastRenderTime = millis();
    Mode_Base::bufferedRenderText = "";
    Mode_Base::bufferedRenderCol = 0;
    Mode_Base::bufferedRenderRow = 0;
    Mode_Base::bufferedRenderClear = clearLcd_none;
}