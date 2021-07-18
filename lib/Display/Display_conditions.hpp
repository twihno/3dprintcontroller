#ifndef DISPLAY_CONDITIOS_HPP_INCLUDED
#define DISPLAY_CONDITIOS_HPP_INCLUDED

#include <Arduino.h>
#include <LEDLighting.hpp>
#include <EnclosurePower.hpp>

extern LEDLighting ledLighting;
extern EnclosurePower enclosurePower;

bool COND_light_off();
bool COND_mode_auto_off();
bool COND_mode_copycat();

#endif
