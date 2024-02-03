#ifndef MODES
#define MODES

enum modes
{
    /**
     * @brief starts to tare
     *
     */
    modes_tare,

    /**
     * @brief default, scale mode.
     *        shows the weight and nothing else.
     */
    modes_scale,

    /**
     * @brief shows the currently selected preset, to brew with
     *        up/down: previous/next preset
     *        ok: start brewing with that preset
     *        cancel: scale
     */
    modes_selectPreset,

    /**
     * @brief the actual brew in-progress.
     *        could be a custom brew or preset brew.
     *        up/down: nothing
     *        ok: nothing
     *        cancel: brewDone
     *
     */
    modes_brew,

    /**
     * @brief stop brewing
     *        up/down: nothing
     *        ok: brewDone
     *        cancel: brewDone
     */
    modes_brewStop,

    /**
     * @brief brew is done
     *        up/down: nothing
     *        ok: scale
     *        cancel: scale
     */
    modes_brewDone,

    /**
     * @brief shows the custom brew menu
     *        up/down: presetsMenu
     *        ok: coffeeWeightMenu
     *        cancel: scale
     *
     */
    modes_customBrewMenu,

    /**
     * @brief asks the user to confirm start of custom brew
     *
     */
    modes_customBrewConfirm,

    /**
     * @brief just shows that this is the presets menu
     *        up/down: sibling menus
     *        ok: configurePreset
     *        cancel: parent menu
     */
    modes_presetsMenu,

    /**
     * @brief shows the currently selected preset, to configure
     *        up/down: previous/next preset
     *        ok: preset configuration menus (e.g. change name, coffee weight)
     *        cancel: parent menu
     */
    modes_configurePreset,

    /**
     * @brief shows the "change name" of preset, menu
     *        up/down: sibling menus
     *        ok: changePresetName
     *        cancel: parent menu
     */
    modes_changePresetNameMenu,
    /**
     * @brief actively change the preset name
     *        up/down: change the current charater shown (that's blinking)
     *        ok: accept the current charater and move to next until the end (next char. should be space)
     *        cancel: do not save new profile name and go to parent
     */
    modes_changePresetName,

    /**
     * @brief shows the coffee weight menu
     *        up/down: sibling menus
     *        ok: coffeeWeightSelection
     *        cancel: parent menuss
     */
    modes_coffeeWeightMenu,
    /**
     * @brief shows the current coffee weight and
     *        allows the user to change that
     *        up/down: change coffee weight
     *        ok: save weight to profile OR to custom brew
     *        cancel: back to coffeeWeightMenu OR customBrewMenu
     * TODO: needs dynamic ok/cancel action
     *
     * TODO: add pointer; to parent/siblings/children; use tuples
     */
    modes_coffeeWeightSelection,

    modes_brewRatioMenu,
    modes_brewRatioSelection,

    modes_brewDurationMenu,
    modes_brewDurationSelection,

    modes_startTimerMenu,
    modes_startTimerSelection,

    modes_stopTimerMenu,
    modes_stopTimerSelection,
};

#endif // MODES