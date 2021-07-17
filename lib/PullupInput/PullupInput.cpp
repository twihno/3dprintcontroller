#include "PullupInput.hpp"

void PullupInput::init(uint8_t input_pin)
{
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
