#include <stdint.h> // uint32_t

#include "Constants.hpp" // ENCLOSUREVENTILATION_TIMEOUT
#include "Ventilation.hpp"

Ventilation::Ventilation()
{
    this->enclosureState = EnclosureVentilationState::OFF;
    externalVentilationReq = false;
}

void Ventilation::tick(uint32_t millis, bool externalSwitchOn, bool isPrinterOn)
{
    switch (enclosureState)
    {
    case EnclosureVentilationState::OFF:
        if (isPrinterOn)
        {
            enclosureState = EnclosureVentilationState::ON;
        }
        break;
    case EnclosureVentilationState::ON:
        if (!isPrinterOn)
        {
            timestamp = millis + ENCLOSUREVENTILATION_TIMEOUT;
            enclosureState = EnclosureVentilationState::SHUTDOWN;
        }
        break;
    case EnclosureVentilationState::SHUTDOWN:
        if (isPrinterOn)
        {
            enclosureState = EnclosureVentilationState::ON;
        }
        else
        {
            if (millis > timestamp)
            {
                enclosureState = EnclosureVentilationState::OFF;
            }
        }
        break;
    }

    updateExternalVentilation(enclosureState != EnclosureVentilationState::OFF, externalSwitchOn);
}

inline void Ventilation::updateExternalVentilation(bool internalVentilationOn, bool externalSwitchOn)
{
    externalVentilationReq = (internalVentilationOn && !externalSwitchOn);
}

bool Ventilation::isEnclosureVentilationOn() // for relay
{
    return !(this->enclosureState == EnclosureVentilationState::OFF);
}

bool Ventilation::isExternalVentilationReq() // for relay
{
    return this->externalVentilationReq;
}

bool Ventilation::isShutdown()
{
    return this->enclosureState == EnclosureVentilationState::SHUTDOWN;
}
