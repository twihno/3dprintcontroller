#ifndef LEDLIGHTING_HPP_INCLUDED
#define LEDLIGHTING_HPP_INCLUDED

#include <stdint.h>

enum LEDLightingState
{
    ON, OFF
};

class LEDLighting
{
private:
    LEDLightingState state;
    uint32_t timestamp;

public:
    LEDLighting();
    void tick(uint32_t);
    void setOn(uint32_t);
    void setOff();
    bool isOn();
};

#endif
