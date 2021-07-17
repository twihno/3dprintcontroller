#ifndef DISPLAY_MENU_HPP_INCLUDED
#define DISPLAY_MENU_HPP_INCLUDED

#include <Arduino.h>
#include <LCDMenuLib2.h>
#include <LiquidCrystal_I2C.h>

#include "Display_constants.hpp"

extern LiquidCrystal_I2C lcd;
extern LCDMenuLib2 LCDML;
extern const char *const g_LCDML_DISP_lang_lcdml_table[] PROGMEM;

void lcdml_menu_clear();
void lcdml_menu_display();

#endif