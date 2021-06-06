#include <stdint.h> // uint32_t
#include <Arduino.h> // millis()

#include "Constants.hpp" // LEDLIGHTING_TIMEOUT
#include "LEDLighting.hpp"

LEDLighting::LEDLighting()
{
    this->state = OFF;
}

void LEDLighting::tick()
{
    if(this->state == ON && millis() - timestamp > LEDLIGHTING_TIMEOUT)
        this->state = OFF;
}

bool LEDLighting::isOn()
{
    return this->state == ON;
}

void LEDLighting::setOn()
{
    this->state = ON;
    this->timestamp = millis();
}

void LEDLighting::setOff()
{
    this->state = OFF;
}
