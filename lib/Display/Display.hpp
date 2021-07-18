#ifndef DISPLAY_HPP_INCLUDED
#define DISPLAY_HPP_INCLUDED

#include <Arduino.h>
#include <Wire.h>
#include <LCDMenuLib2.h>

#include "Printer_LiquidCrystal_I2C.hpp"
#include "Display_constants.hpp"
#include "Display_control.hpp"
#include "Display_menu.hpp"
#include "Display_functions.hpp"
#include "Display_conditions.hpp"

// custom characters
const uint8_t scroll_bar[5][8] = {
    {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
    {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1
    {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
    {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
    {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
};

const uint8_t custom_characters[2][8] = {
    {B00100, B01010, B01010, B01010, B01010, B10001, B10001, B01110}, // Thermometer
    {B01110, B10001, B10001, B10001, B01110, B01110, B01110, B00100}  // Lampe
};

void display_setup();
void display_loop();

#endif