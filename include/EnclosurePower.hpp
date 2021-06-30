#ifndef ENCLOSUREPOWER_HPP_INCLUDED
#define ENCLOSUREPOWER_HPP_INCLUDED

#include <stdint.h>

enum class EnclosurePowerState
{
    RUNNING,
    STANDBY,
    SHUTDOWN,
    OFF
};

class EnclosurePower
{
private:
    EnclosurePowerState state = EnclosurePowerState::OFF;
    bool autoOff = true;
    uint32_t timestamp = 0;

public:
    EnclosurePower(void);
    void enableAutoOff();
    void disableAutoOff();
    void tick(uint32_t millis, bool isPrinterOn);
    void abort();
    void setOn();
    void setOff();
    uint32_t getShutdownTimer(uint32_t millis);
    bool isPowerActive();
    bool isShutdown();
    bool isPrinterRunning();
    bool isAutoOff();
};

#endif
