#ifndef DISPLAY_FUNCTIONS_HPP_INCLUDED
#define DISPLAY_FUNCTIONS_HPP_INCLUDED

#include <stdint.h>
#include <LCDMenuLib2.h>

#include "Constants.hpp"
#include "Printer_LiquidCrystal_I2C.hpp"
#include "Display_constants.hpp"
#include "LEDLighting.hpp"

extern Printer_LiquidCrystal_I2C lcd;
extern LCDMenuLib2 LCDML;
extern LEDLighting ledLighting;

void updateMenuLoop(void);
void printScreensaver(bool redraw);
void printTemp(void);
void printLight(void);

void mFunc_screensaver(uint8_t param);
void mFunc_turnOnLight(uint8_t param);
void mFunc_turnOffLight(uint8_t param);

#endif