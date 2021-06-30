#ifndef PULLUPINPUT_HPP_INCLUDED
#define PULLUPINPUT_HPP_INCLUDED

#include <Arduino.h>
#include <stdint.h>

class PullupInput
{
private:
    uint8_t pin;

public:
    explicit PullupInput(uint8_t input_pin);

    virtual bool isOn(), isOff();
};

#endif
