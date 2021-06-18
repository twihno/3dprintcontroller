#ifndef ENCLOSUREPOWER_HPP_INCLUDED
#define ENCLOSUREPOWER_HPP_INCLUDED

#include <stdint.h>

enum class EnclosurePowerState
{
    ON, OFF
};

class EnclosurePower
{
private:
    EnclosurePowerState state;
    bool autoOff;
    uint32_t timestamp;

public:
    EnclosurePower();
    void enableAutoOff();
    void disableAutoOff();
    void tick(uint32_t);
    void setOn(uint32_t);
    void setOff();
    bool isOn();
};

#endif