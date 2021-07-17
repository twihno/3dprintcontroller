#ifndef DISPLAY_CONTROL_HPP_INCLUDED
#define DISPLAY_CONTROL_HPP_INCLUDED

#include <Arduino.h>
#include <Encoder.h>
#include <LCDMenuLib2.h>

#define encoder_A_pin 20      // physical pin has to be 2 or 3 to use interrupts (on mega e.g. 20 or 21), use internal pullups
#define encoder_B_pin 21      // physical pin has to be 2 or 3 to use interrupts (on mega e.g. 20 or 21), use internal pullups
#define encoder_button_pin 49 // physical pin , use internal pullup

#define g_LCDML_CONTROL_button_long_press 800  // ms
#define g_LCDML_CONTROL_button_short_press 120 // ms

#define ENCODER_OPTIMIZE_INTERRUPTS //Only when using pin2/3 (or 20/21 on mega)

extern LCDMenuLib2 LCDML;

void lcdml_menu_control(void);

#endif