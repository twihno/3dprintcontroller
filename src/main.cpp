#include <Arduino.h>

#include "PullupInput.hpp"
#include "Relay.hpp"
#include "EnclosurePower.hpp"
#include "LEDLighting.hpp"
#include "Ventilation.hpp"
#include "PrinterInput.hpp"
#include "CachedPullupInput.hpp"

// Input
PrinterInput printerInput = PrinterInput(22);
CachedPullupInput externalVentilationSwitch = CachedPullupInput(24);

// Output
Relay powerArduino = Relay(37, LOW);
Relay powerLight = Relay(29, LOW);
Relay powerEnclosure = Relay(31, LOW);
Relay powerEnclosureVentilation = Relay(33, LOW);
Relay powerExternalVentilation = Relay(35, LOW);

// Control
EnclosurePower enclosurePower = EnclosurePower();
LEDLighting ledLighting = LEDLighting();
Ventilation ventilation = Ventilation();

//cppcheck-suppress unusedFunction
void setup()
{
    powerArduino.setState(true);
    enclosurePower.setOn();
}

//cppcheck-suppress unusedFunction
void loop()
{
    // Read
    printerInput.read(millis());
    externalVentilationSwitch.read();

    enclosurePower.tick(millis(), printerInput.isOn());
    ledLighting.tick(millis());
    ventilation.tick(millis(), externalVentilationSwitch.isOn(), printerInput.isOn());

    // Write
    powerArduino.setState(enclosurePower.isPowerActive());
    powerLight.setState(ledLighting.isOn());
    powerEnclosure.setState(enclosurePower.isPowerActive());
    powerEnclosureVentilation.setState(ventilation.isEnclosureVentilationOn());
    powerExternalVentilation.setState(ventilation.isExternalVentilationReq());
}
