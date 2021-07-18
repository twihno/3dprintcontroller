#ifndef DISPLAY_FUNCTIONS_HPP_INCLUDED
#define DISPLAY_FUNCTIONS_HPP_INCLUDED

#include <stdint.h>
#include <LCDMenuLib2.h>

#include "Constants.hpp"
#include "Printer_LiquidCrystal_I2C.hpp"
#include "Display_constants.hpp"
#include "LEDLighting.hpp"
#include "EnclosurePower.hpp"
#include "Ventilation.hpp"

extern Printer_LiquidCrystal_I2C lcd;
extern LCDMenuLib2 LCDML;
extern LEDLighting ledLighting;
extern EnclosurePower enclosurePower;
extern Ventilation ventilation;

extern void shutdown(void);

void updateMenuLoop(void);
void printScreensaver(bool redraw);
void printTemp(void);
void printLight(void);
void printMode(void);
void printExternalVentilationState(void);
void printInternalVentilationState(void);
void printShutdownPopup(bool redraw);

void mFunc_screensaver(uint8_t param);
void mFunc_turnOnLight(uint8_t param);
void mFunc_turnOffLight(uint8_t param);
void mFunc_changeMode(uint8_t param);
void mFunc_shutdownPopup(uint8_t param);
void mFunc_shutdown(uint8_t param);

#endif