#ifndef CACHEDPULLUPINPUT_HPP_INCLUDED
#define CACHEDPULLUPINPUT_HPP_INCLUDED

#include <stdint.h>
#include "PullupInput.hpp"

class CachedPullupInput : public PullupInput
{
private:
    bool state = false;

public:
    CachedPullupInput(void) = default;
    void read(void);
    bool isOn(void) override;
    bool isOff(void) override;
};

#endif
