#ifndef BUTTON_STATES
#define BUTTON_STATES

enum button_states
{
    /**
     * @brief not pressed
     */
    button_up,
    /**
     * @brief currently down/pressed and first loop (take action)
     *
     */
    button_pressed,
    /**
     * @brief still down/pressed (consecutive loop, for long press actions)
     *
     */
    button_down,
    /**
     * @brief ignore due to navigation
     *
     */
    button_ignore,
};

#endif // BUTTON_STATES