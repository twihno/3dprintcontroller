#include <Arduino.h>

#include "Constants.hpp"
#include "PullupInput.hpp"
#include "Relay.hpp"
#include "EnclosurePower.hpp"
#include "LEDLighting.hpp"
#include "Ventilation.hpp"
#include "PrinterInput.hpp"
#include "CachedPullupInput.hpp"
#include "Display.hpp"

// Input
PrinterInput printerInput;
CachedPullupInput externalVentilationSwitch;

// Output
Relay powerArduino;
Relay powerLight;
Relay powerEnclosure;
Relay powerEnclosureVentilation;
Relay powerExternalVentilation;

// Control
EnclosurePower enclosurePower = EnclosurePower();
LEDLighting ledLighting = LEDLighting();
Ventilation ventilation = Ventilation();

//cppcheck-suppress unusedFunction
void setup()
{
    // Set pin modes
    // INPUT
    pinMode(PRINTER_INPUT_PIN, INPUT_PULLUP);
    printerInput.init(PRINTER_INPUT_PIN);
    pinMode(EXTERNAL_VENTILATION_SWITCH_PIN, INPUT_PULLUP);
    externalVentilationSwitch.init(EXTERNAL_VENTILATION_SWITCH_PIN);

    // OUTPUT
    pinMode(PWR_ARDUINO_PIN, OUTPUT);
    powerArduino.init(PWR_ARDUINO_PIN, HIGH);
    pinMode(PWR_LIGHT_PIN, OUTPUT);
    powerLight.init(PWR_LIGHT_PIN, HIGH);
    pinMode(PWR_ENCLOSURE_PIN, OUTPUT);
    powerEnclosure.init(PWR_ENCLOSURE_PIN, HIGH);
    pinMode(PWR_ENCLOSURE_VENT_PIN, OUTPUT);
    powerEnclosureVentilation.init(PWR_ENCLOSURE_VENT_PIN, HIGH);
    pinMode(PWR_EXTERNAL_VENT_PIN, OUTPUT);
    powerExternalVentilation.init(PWR_EXTERNAL_VENT_PIN, HIGH);

    powerArduino.setState(true);
    enclosurePower.setOn();

    display_setup();
}

//cppcheck-suppress unusedFunction
void loop()
{
    // Read
    printerInput.read(millis());
    externalVentilationSwitch.read();

    // Process

    enclosurePower.tick(millis(), printerInput.isOn());
    ledLighting.tick(millis());
    ventilation.tick(millis(), externalVentilationSwitch.isOn(), printerInput.isOn());

    display_loop();

    // Write
    powerArduino.setState(enclosurePower.isPowerActive());
    powerLight.setState(ledLighting.isOn());
    powerEnclosure.setState(enclosurePower.isPowerActive());
    powerEnclosureVentilation.setState(ventilation.isEnclosureVentilationOn());
    powerExternalVentilation.setState(ventilation.isExternalVentilationReq());
}
