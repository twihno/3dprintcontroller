#ifndef VENTILATION_HPP_INCLUDED
#define VENTILATION_HPP_INCLUDED

#include <stdint.h>

enum class EnclosureVentilationState
{
    ON,
    SHUTDOWN,
    OFF
};

class Ventilation
{
private:
    EnclosureVentilationState enclosureState;
    bool externalVentilationReq;
    uint32_t timestamp;
    inline void updateExternalVentilation(bool internalVentilationOn, bool externalSwitchOn);

public:
    Ventilation();
    void tick(uint32_t millis, bool externalSwitchOn, bool isPrinterOn);
    bool isEnclosureVentilationOn();
    bool isExternalVentilationReq();
    bool isShutdown();
};

#endif
