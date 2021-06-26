#ifndef ENCLOSUREPOWER_HPP_INCLUDED
#define ENCLOSUREPOWER_HPP_INCLUDED

#include <stdint.h>

enum class EnclosurePowerState
{
    ON,
    SHUTDOWN,
    OFF
};

enum class PrinterState
{
    RUNNING,
    STANDBY
};

class EnclosurePower
{
private:
    EnclosurePowerState state;
    PrinterState printerState;
    bool autoOff;
    uint32_t timestamp;

public:
    EnclosurePower();
    void enableAutoOff();
    void disableAutoOff();
    void tick(uint32_t, bool);
    void abort();
    void setOn();
    void setOff();
    uint32_t getShutdownTimer(uint32_t);
    bool isPowerActive();
    bool isShutdown();
    bool isPrinterRunning();
    bool isAutoOff();
};

#endif
