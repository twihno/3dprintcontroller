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

class PrinterInput : public PullupInput
{
private:
    PrinterState state = PrinterState::OFF;
    uint32_t timestamp;

public:
    PrinterInput(uint8_t input_pin) : PullupInput(input_pin) {};
    void read(uint32_t millis);
    bool isOn(), isOff();
};

#endif
