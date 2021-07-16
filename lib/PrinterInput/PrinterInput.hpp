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
    uint32_t timestamp = 0;

public:
    PrinterInput(void) = default;
    void read(uint32_t millis);
    bool isOn() override;
    bool isOff() override;
};

#endif
