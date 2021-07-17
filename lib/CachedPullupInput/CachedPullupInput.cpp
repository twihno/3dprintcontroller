#include "CachedPullupInput.hpp"

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
