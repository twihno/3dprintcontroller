#include <stdint.h> // uint32_t

#include "Constants.hpp" // PRINTER_ON_TOLERANCE, PRINTER_OFF_TOLERANCE
#include "PrinterInput.hpp"

//PullupInput pullupInput;

PrinterInput::PrinterInput(uint8_t input_pin)
{
    this->state = PrinterState::OFF;
    //this->pullupInput = PullupInput(input_pin);
}

void PrinterInput::read(uint32_t millis)
{
}
