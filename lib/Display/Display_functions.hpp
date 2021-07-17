#ifndef DISPLAY_FUNCTIOS_HPP_INCLUDED
#define DISPLAY_FUNCTIOS_HPP_INCLUDED

#include <stdint.h>
#include <LCDMenuLib2.h>
#include <LiquidCrystal_I2C.h>

#include "Display_constants.hpp"

extern LiquidCrystal_I2C lcd;
extern LCDMenuLib2 LCDML;

#include "Display_functions.hpp"

void mFunc_information(uint8_t param);
uint8_t g_func_timer_info = 0; // time counter (global variable)
unsigned long g_timer_1 = 0;   // timer variable (global variable)
void mFunc_timer_info(uint8_t param);
uint8_t g_button_value = 0; // button value counter (global variable)
void mFunc_p2(uint8_t param);
void mFunc_screensaver(uint8_t param);
void mFunc_back(uint8_t param);
void mFunc_goToRootMenu(uint8_t param);
void mFunc_jumpTo_timer_info(uint8_t param);

#endif