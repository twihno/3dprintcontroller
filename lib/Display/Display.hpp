#ifndef DISPLAY_HPP_INCLUDED
#define DISPLAY_HPP_INCLUDED

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCDMenuLib2.h>

#include "Display_constants.hpp"
#include "Display_control.hpp"
#include "Display_menu.hpp"
#include "Display_functions.hpp"

// custom characters
const uint8_t scroll_bar[5][8] = {
    {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
    {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1
    {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
    {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
    {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
};

void display_setup();
void display_loop();

#endif