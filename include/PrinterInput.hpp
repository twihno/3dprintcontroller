#ifndef PRINTERINPUT_HPP_INCLUDED
#define PRINTERINPUT_HPP_INCLUDED

#include <stdint.h>
#include "PullupInput.hpp"

enum class PrinterState
{
    ON,
    STARTUP,
    SHUTDOWN,
    OFF
};

class PrinterInput
{
private:
    PrinterState state;
    //extern PullupInput pullupInput;
    uint32_t timestamp;

public:
    PrinterInput(uint8_t input_pin);
    void read(uint32_t millis);
    bool isOn();
};

#endif
