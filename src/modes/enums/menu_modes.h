#ifndef MENU_MODES
#define MENU_MODES

/**
 * @brief the type of menu mode we're in for certain modes,
 * to know where to go when clicking ok/cancel/etc.
 *
 */
enum menu_modes
{
    menu_modes_customBrew,
    menu_modes_configurePreset
};

#endif // MENU_MODES