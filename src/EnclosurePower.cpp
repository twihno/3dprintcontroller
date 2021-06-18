#include <stdint.h> // uint32_t

#include "Constants.hpp" // ENCLOSUREPOWER_TIMEOUT
#include "EnclosurePower.hpp"

EnclosurePower::EnclosurePower()
{
    this->state = EnclosurePowerState::OFF;
    this->autoOff = true;
}

void EnclosurePower::tick(uint32_t millis)
{
    bool timedOut = millis > timestamp; 
    if(isOn() && this->autoOff && timedOut)
    {
        this->state = EnclosurePowerState::OFF;
    }
}

bool EnclosurePower::isOn()
{
    return this->state == EnclosurePowerState::ON;
}

void EnclosurePower::setOn(uint32_t millis)
{
    this->state = EnclosurePowerState::ON;
    this->timestamp = millis + ENCLOSUREPOWER_TIMEOUT;
}

void EnclosurePower::setOff()
{
    this->state = EnclosurePowerState::OFF;
}

void EnclosurePower::enableAutoOff()
{
    this->autoOff = true;
}

void EnclosurePower::disableAutoOff()
{
    this->autoOff = false;
}