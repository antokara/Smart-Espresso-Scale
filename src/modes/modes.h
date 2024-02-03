#ifndef MODES
#define MODES

enum modes
{
    /**
     * @brief starts to tare
     *
     */
    tare,

    /**
     * @brief default, scale mode.
     *        shows the weight and nothing else.
     */
    scale,

    /**
     * @brief shows the currently selected preset, to brew with
     *        up/down: previous/next preset
     *        ok: start brewing with that preset
     *        cancel: scale
     */
    selectPreset,

    /**
     * @brief the actual brew in-progress.
     *        could be a custom brew or preset brew.
     *        up/down: nothing
     *        ok: nothing
     *        cancel: brewDone
     *
     */
    brew,

    /**
     * @brief stop brewing
     *        up/down: nothing
     *        ok: brewDone
     *        cancel: brewDone
     */
    brewStop,

    /**
     * @brief brew is done
     *        up/down: nothing
     *        ok: scale
     *        cancel: scale
     */
    brewDone,

    /**
     * @brief shows the custom brew menu
     *        up/down: presetsMenu
     *        ok: coffeeWeightMenu
     *        cancel: scale
     *
     */
    customBrewMenu,

    /**
     * @brief asks the user to confirm start of custom brew
     *
     */
    customBrewConfirm,

    /**
     * @brief just shows that this is the presets menu
     *        up/down: sibling menus
     *        ok: configurePreset
     *        cancel: parent menu
     */
    presetsMenu,

    /**
     * @brief shows the currently selected preset, to configure
     *        up/down: previous/next preset
     *        ok: preset configuration menus (e.g. change name, coffee weight)
     *        cancel: parent menu
     */
    configurePreset,

    /**
     * @brief shows the "change name" of preset, menu
     *        up/down: sibling menus
     *        ok: changePresetName
     *        cancel: parent menu
     */
    changePresetNameMenu,
    /**
     * @brief actively change the preset name
     *        up/down: change the current charater shown (that's blinking)
     *        ok: accept the current charater and move to next until the end (next char. should be space)
     *        cancel: do not save new profile name and go to parent
     */
    changePresetName,

    /**
     * @brief shows the coffee weight menu
     *        up/down: sibling menus
     *        ok: coffeeWeightSelection
     *        cancel: parent menuss
     */
    coffeeWeightMenu,
    /**
     * @brief shows the current coffee weight and
     *        allows the user to change that
     *        up/down: change coffee weight
     *        ok: save weight to profile OR to custom brew
     *
     */
    coffeeWeightSelection,

    brewRatioMenu,
    brewRatioSelection,

    brewDurationMenu,
    brewDurationSelection,

    startTimerMenu,
    startTimerSelection,

    stopTimerMenu,
    stopTimerSelection,
};

#endif // MODES