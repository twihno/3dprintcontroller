#include <stdint.h> // uint32_t

#include "Constants.hpp" // ENCLOSUREVENTILATION_TIMEOUT
#include "Ventilation.hpp"

Ventilation::Ventilation()
{
    this->enclosureState = EnclosureVentilationState::OFF;
    this->externalState = ExternalVentilationState::OFF;
    this->autoOff = true;
}

/*void Ventilation::tick(uint32_t millis, bool externalSwitchOn)
{
    if (externalSwitchOn)
    {
        externalState = ExternalVentilationState::EXTERNAL_ON;
    }

    bool timedOut = millis > timestamp;
    if (isEnclosureOn() && this->autoOff && timedOut)
    {
        this->state = EnclosurePowerState::OFF;
    }
}*/

bool Ventilation::isEnclosureOn()
{
    return this->enclosureState == EnclosureVentilationState::ON;
}

bool Ventilation::isExternalOn()
{
    return this->externalState == ExternalVentilationState::ON;
}

void Ventilation::enableAutoOff()
{
    this->autoOff = true;
}

void Ventilation::disableAutoOff()
{
    this->autoOff = false;
}
