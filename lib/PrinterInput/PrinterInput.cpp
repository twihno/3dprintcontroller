#include <stdint.h> // uint32_t

#include "Constants.hpp" // PRINTER_ON_TOLERANCE, PRINTER_OFF_TOLERANCE
#include "PrinterInput.hpp"

void PrinterInput::read(uint32_t millis)
{
    switch(this->state) 
    {
        case PrinterState::ON:
            if(PullupInput::isOff()) 
            {
                this->timestamp = millis + PRINTER_OFF_TOLERANCE;
                this->state = PrinterState::SHUTDOWN;
            }
            break;
        case PrinterState::STARTUP:
            if(PullupInput::isOff()) 
            {
                this->state = PrinterState::OFF;
            } 
            else if(millis > timestamp) 
            {
                this->state = PrinterState::ON;
            }
            break;
        case PrinterState::SHUTDOWN:
            if(PullupInput::isOn()) 
            {
                this->state = PrinterState::ON;
            } 
            else if(millis > timestamp) 
            {
                this->state = PrinterState::OFF;
            }
            break;
        case PrinterState::OFF:
            if(PullupInput::isOn()) 
            {
                this->timestamp = millis + PRINTER_ON_TOLERANCE;
                this->state = PrinterState::STARTUP;
            }
            break;
    }
}

bool PrinterInput::isOn()
{
    return this->state == PrinterState::ON || this->state == PrinterState::SHUTDOWN;
}

bool PrinterInput::isOff()
{
    return this->state == PrinterState::OFF || this->state == PrinterState::STARTUP;
}