#ifndef LEDLIGHTING_HPP_INCLUDED
#define LEDLIGHTING_HPP_INCLUDED

#include <stdint.h>

enum class LEDLightingState
{
    ON,
    OFF
};

class LEDLighting
{
private:
    LEDLightingState state;
    uint32_t timestamp;

public:
    LEDLighting();
    void tick(uint32_t millis);
    void setOn(uint32_t millis);
    void setOff();
    bool isOn();
    uint32_t getTimestamp();
};

#endif
