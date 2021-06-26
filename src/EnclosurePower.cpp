#include <stdint.h> // uint32_t

#include "Constants.hpp" // ENCLOSUREPOWER_TIMEOUT
#include "EnclosurePower.hpp"

EnclosurePower::EnclosurePower()
{
    this->state = EnclosurePowerState::OFF;
    this->printerState = PrinterState::STANDBY;
    this->autoOff = true;
}

void EnclosurePower::tick(uint32_t millis, bool isPrinterOn)
{
    if (printerState == PrinterState::RUNNING)
    {
        switch (state)
        {
        case EnclosurePowerState::OFF:
            // unreachable
            break;
        case EnclosurePowerState::ON:
            if (!isPrinterOn)
            {
                if (autoOff)
                {
                    this->timestamp = millis + ENCLOSUREPOWER_TIMEOUT;
                    this->printerState = PrinterState::STANDBY;
                    this->state = EnclosurePowerState::SHUTDOWN;
                }
                else
                {
                    this->printerState = PrinterState::STANDBY;
                }
            }
            break;
        case EnclosurePowerState::SHUTDOWN:
            // not in use
            break;
        }
    }
    else
    {
        switch (state)
        {
        case EnclosurePowerState::OFF:
            // do nothing (for now)
            break;
        case EnclosurePowerState::ON:
            if (isPrinterOn)
            {
                this->printerState = PrinterState::RUNNING;
            }
            break;
        case EnclosurePowerState::SHUTDOWN:
            if (isPrinterOn)
            {
                this->printerState = PrinterState::RUNNING;
                this->state = EnclosurePowerState::ON;
            }
            else if (millis > timestamp)
            {
                this->state = EnclosurePowerState::OFF;
            }
            break;
        }
    }
}

void EnclosurePower::abort()
{
    if (this->state == EnclosurePowerState::SHUTDOWN && this->printerState == PrinterState::STANDBY)
    {
        this->printerState = PrinterState::STANDBY;
        this->state = EnclosurePowerState::ON;
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
    return this->printerState == PrinterState::RUNNING;
}

void EnclosurePower::setOn()
{
    this->state = EnclosurePowerState::ON;
}

void EnclosurePower::setOff()
{
    this->state = EnclosurePowerState::OFF;
    this->printerState = PrinterState::STANDBY;
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
