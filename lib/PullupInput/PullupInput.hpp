#ifndef PULLUPINPUT_HPP_INCLUDED
#define PULLUPINPUT_HPP_INCLUDED

#include <Arduino.h>

class PullupInput
{
private:
    unsigned int pin;

public:
    PullupInput(unsigned int input_pin);

    bool isOn();

    bool isOff();
};

#endif
