#include <stdint.h> // uint32_t

#include "Constants.hpp" // LEDLIGHTING_TIMEOUT
#include "LEDLighting.hpp"

LEDLighting::LEDLighting()
{
    this->state = LEDLightingState::OFF;
}

void LEDLighting::tick(uint32_t millis)
{
    if (this->state == LEDLightingState::ON_TEMPORARY && (millis > timestamp))
    {
        this->state = LEDLightingState::OFF;
        this->timestamp = 0;
    }
}

bool LEDLighting::isOn()
{
    return this->state != LEDLightingState::OFF;
}

void LEDLighting::setOnPermanent()
{
    this->state = LEDLightingState::ON_PERMANENT;
}

void LEDLighting::setOnTemporary(uint32_t millis)
{
    this->state = LEDLightingState::ON_TEMPORARY;
    this->timestamp = millis + LEDLIGHTING_TIMEOUT;
}

void LEDLighting::setOff()
{
    this->state = LEDLightingState::OFF;
    this->timestamp = 0;
}

uint32_t LEDLighting::getTimestamp()
{
    return timestamp;
}
