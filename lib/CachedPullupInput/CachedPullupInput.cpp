#include "CachedPullupInput.hpp"

CachedPullupInput::CachedPullupInput(uint8_t input_pin) : PullupInput(input_pin)
{
    this->state = false;
}

void CachedPullupInput::read(void)
{
    this->state = PullupInput::isOn();
}

bool CachedPullupInput::isOn(void)
{
    return this->state;
}

bool CachedPullupInput::isOff(void)
{
    return !(this->state);
}
