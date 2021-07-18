#ifndef PRINTER_LIQUIDCRYSTAL_I2C_HPP_INCLUDED
#define PRINTER_LIQUIDCRYSTAL_I2C_HPP_INCLUDED

#include <stdint.h>
#include <LiquidCrystal_I2C.h>

class Printer_LiquidCrystal_I2C : public LiquidCrystal_I2C
{
private:
    uint32_t timestamp = 0;
    void turnOffBacklight(void);

public:
    Printer_LiquidCrystal_I2C(void) = default;
    Printer_LiquidCrystal_I2C(uint8_t a, uint8_t b, uint8_t c) : LiquidCrystal_I2C(a, b, c) {}
    void turnOnBacklight(uint32_t millis);
    void tick(uint32_t millis);
};

#endif
