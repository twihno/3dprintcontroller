#include "PullupInput.hpp"

PullupInput::PullupInput(uint8_t input_pin)
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
