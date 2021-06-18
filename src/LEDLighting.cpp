#include <stdint.h> // uint32_t

#include "Constants.hpp" // LEDLIGHTING_TIMEOUT
#include "LEDLighting.hpp"

LEDLighting::LEDLighting()
{
    this->state = LEDLightingState::OFF;
}

void LEDLighting::tick(uint32_t millis)
{
    bool timedOut = millis > timestamp;
    if(isOn() && timedOut)
    {
        this->state = LEDLightingState::OFF;
    }
}

bool LEDLighting::isOn()
{
    return this->state == LEDLightingState::ON;
}

void LEDLighting::setOn(uint32_t millis)
{
    this->state = LEDLightingState::ON;
    this->timestamp = millis + LEDLIGHTING_TIMEOUT;
}

void LEDLighting::setOff()
{
    this->state = LEDLightingState::OFF;
}
