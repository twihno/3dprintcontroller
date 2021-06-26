#ifndef VENTILATION_HPP_INCLUDED
#define VENTILATION_HPP_INCLUDED

#include <stdint.h>

enum class EnclosureVentilationState
{
    ON,
    OFF
};

enum class ExternalVentilationState
{
    ON,
    EXTERNAL_ON,
    OFF
};

class Ventilation
{
private:
    EnclosureVentilationState enclosureState;
    ExternalVentilationState externalState;
    bool autoOff;
    uint32_t timestamp;

public:
    Ventilation();
    void enableAutoOff();
    void disableAutoOff();
    void tick(uint32_t, bool);
    bool isEnclosureOn();
    bool isExternalOn();
};

#endif
