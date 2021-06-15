#ifndef PULLUPINPUT_HPP_INCLUDED
#define PULLUPINPUT_HPP_INCLUDED

#include <Arduino.h>
#include <stdint.h>

class PullupInput
{
private:
    uint8_t pin;

public:
    PullupInput(uint8_t input_pin);

    bool isOn();

    bool isOff();
};

#endif
