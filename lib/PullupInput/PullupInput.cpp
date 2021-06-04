#include "PullupInput.hpp"

PullupInput::PullupInput(unsigned int input_pin)
{
    pinMode(pin, INPUT_PULLUP);
    pin = input_pin;
}

bool PullupInput::isOn()
{
    return !digitalRead(this->pin);
}

bool PullupInput::isOff()
{
    return digitalRead(this->pin);
}
