#ifndef DISPLAY_FUNCTIONS_HPP_INCLUDED
#define DISPLAY_FUNCTIONS_HPP_INCLUDED

#include <stdint.h>
#include <LCDMenuLib2.h>
#include <LiquidCrystal_I2C.h>

#include "Display_constants.hpp"

extern LiquidCrystal_I2C lcd;
extern LCDMenuLib2 LCDML;

#include "Display_functions.hpp"

void mFunc_information(uint8_t param);
void mFunc_timer_info(uint8_t param);
void mFunc_p2(uint8_t param);
void mFunc_screensaver(uint8_t param);
void mFunc_back(uint8_t param);
void mFunc_goToRootMenu(uint8_t param);
void mFunc_jumpTo_timer_info(uint8_t param);

#endif