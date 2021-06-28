#include <stdint.h> // uint32_t

#include "Constants.hpp" // ENCLOSUREPOWER_TIMEOUT
#include "EnclosurePower.hpp"

EnclosurePower::EnclosurePower()
{
    this->state = EnclosurePowerState::OFF;
    this->autoOff = true;
}

void EnclosurePower::tick(uint32_t millis, bool isPrinterOn)
{

    switch (state)
    {
    case EnclosurePowerState::RUNNING:
        if (!isPrinterOn)
        {
            if (autoOff)
            {
                this->timestamp = millis + ENCLOSUREPOWER_TIMEOUT;
                this->state = EnclosurePowerState::SHUTDOWN;
            }
            else
            {
                this->state = EnclosurePowerState::STANDBY;
            }
        }
        break;
    case EnclosurePowerState::STANDBY:
        if (isPrinterOn)
        {
            this->state = EnclosurePowerState::RUNNING;
        }
        break;
    case EnclosurePowerState::SHUTDOWN:
        if (isPrinterOn)
        {
            this->state = EnclosurePowerState::RUNNING;
        }
        else if (millis > timestamp)
        {
            this->state = EnclosurePowerState::OFF;
        }
        break;
    case EnclosurePowerState::OFF:
        // do nothing (for now)
        break;
    }
}

void EnclosurePower::abort()
{
    if (this->state == EnclosurePowerState::SHUTDOWN)
    {
        this->state = EnclosurePowerState::STANDBY;
    }
}

bool EnclosurePower::isPowerActive()
{
    return this->state != EnclosurePowerState::OFF;
}

bool EnclosurePower::isShutdown()
{
    return this->state == EnclosurePowerState::SHUTDOWN;
}

bool EnclosurePower::isPrinterRunning()
{
    return this->state == EnclosurePowerState::RUNNING;
}

void EnclosurePower::setOn()
{
    if (!(this->state == EnclosurePowerState::RUNNING))
    {
        this->state = EnclosurePowerState::STANDBY;
    }
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

uint32_t EnclosurePower::getShutdownTimer(uint32_t millis)
{
    if (millis > timestamp)
    {
        return 0;
    }
    else
    {
        return timestamp - millis;
    }
}

bool EnclosurePower::isAutoOff()
{
    return this->autoOff;
}
