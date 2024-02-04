#ifndef BREW_STAGES
#define BREW_STAGES

enum brew_stages
{
    /**
     * @brief when the timer has not started yet.
     * depends on start timer.
     *
     */
    brew_stage_waiting,
    /**
     * @brief the timer has started
     *
     */
    brew_stage_in_progress,
    /**
     * @brief the pump has stopped but
     * if stop timer is set to last drop, it may be still dripping
     *
     */
    brew_stage_stopping,
    /**
     * @brief no more dripping. show the "summary"
     *
     */
    brew_stage_done
};

#endif // BREW_STAGES