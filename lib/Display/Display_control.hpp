#ifndef DISPLAY_CONTROL_HPP_INCLUDED
#define DISPLAY_CONTROL_HPP_INCLUDED

#include <Arduino.h>
#include <Encoder.h>
#include <LCDMenuLib2.h>

#include "Printer_LiquidCrystal_I2C.hpp"

#define encoder_A_pin 2      // physical pin has to be 2 or 3 to use interrupts (on mega e.g. 20 or 21), use internal pullups
#define encoder_B_pin 3      // physical pin has to be 2 or 3 to use interrupts (on mega e.g. 20 or 21), use internal pullups
#define encoder_button_pin 5 // physical pin , use internal pullup

#define g_LCDML_CONTROL_button_long_press 800  // ms
#define g_LCDML_CONTROL_button_short_press 120 // ms

#define ENCODER_OPTIMIZE_INTERRUPTS //Only when using pin2/3 (or 20/21 on mega)

extern LCDMenuLib2 LCDML;
extern Printer_LiquidCrystal_I2C lcd;

void lcdml_menu_control(void);

#endif