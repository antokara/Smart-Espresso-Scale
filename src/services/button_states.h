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
     * @brief still down/pressed (consecutive loop, no action usually)
     *
     */
    button_down,
    /**
     * @brief ignore due to navigation
     *
     */
    button_ignore,
};
