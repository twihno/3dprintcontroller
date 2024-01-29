#include <stdint.h> // uint32_t

#include "Constants.hpp" // BACKLIGHT_TIMEOUT
#include "Printer_LiquidCrystal_I2C.hpp"

void Printer_LiquidCrystal_I2C::tick(uint32_t millis)
{
    if (millis > timestamp)
    {
        this->turnOffBacklight();
    }
}

void Printer_LiquidCrystal_I2C::turnOnBacklight(uint32_t millis)
{
    this->backlight();
    this->timestamp = millis + BACKLIGHT_TIMEOUT;
}

void Printer_LiquidCrystal_I2C::turnOffBacklight()
{
    this->clear();
    this->noBacklight();
}
