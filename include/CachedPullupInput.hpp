#ifndef CACHEDPULLUPINPUT_HPP_INCLUDED
#define CACHEDPULLUPINPUT_HPP_INCLUDED

#include <stdint.h>
#include "PullupInput.hpp"

class CachedPullupInput : public PullupInput
{
private:
    bool state;

public:
    CachedPullupInput(uint8_t input_pin);
    void read(void);
    bool isOn(void), isOff(void);
};

#endif
