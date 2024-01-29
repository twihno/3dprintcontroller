#include "Display_conditions.hpp"

#include <Arduino.h>

/* ===================================================================== *
 *                                                                       *
 * Conditions to show or hide a menu element on the display              *
 *                                                                       *
 * ===================================================================== *
 */

bool COND_light_off()
{
    return ledLighting.isOn();
}

bool COND_light_on()
{
    return !ledLighting.isOn();
}

bool COND_mode_auto_off()
{
    return enclosurePower.isAutoOff();
}

bool COND_mode_copycat()
{
    return !enclosurePower.isAutoOff();
}

bool COND_false()
{
    return false;
}
