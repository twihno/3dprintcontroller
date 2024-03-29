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

#define INIT_PULLUPINPUT(INPUT, PIN) \
    pinMode(PIN, INPUT_PULLUP);      \
    INPUT.init(PIN);

#define INIT_LOW_RELAIS(RELAIS, PIN) \
    pinMode(PIN, OUTPUT);            \
    RELAIS.init(PIN, LOW);

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

uint32_t currentMillis;

// cppcheck-suppress unusedFunction
void setup()
{
    // Set pin modes

    // INPUT
    INIT_PULLUPINPUT(printerInput, PRINTER_INPUT_PIN)
    INIT_PULLUPINPUT(externalVentilationSwitch, EXTERNAL_VENTILATION_SWITCH_PIN)

    // OUTPUT
    INIT_LOW_RELAIS(powerArduino, PWR_ARDUINO_PIN)
    INIT_LOW_RELAIS(powerLight, PWR_LIGHT_PIN)
    INIT_LOW_RELAIS(powerEnclosure, PWR_ENCLOSURE_PIN)
    INIT_LOW_RELAIS(powerEnclosureVentilation, PWR_ENCLOSURE_VENT_PIN)
    INIT_LOW_RELAIS(powerExternalVentilation, PWR_EXTERNAL_VENT_PIN)

    powerArduino.setState(true);
    enclosurePower.setOn();

    display_setup();
}

// cppcheck-suppress unusedFunction
void loop()
{
    currentMillis = millis();

    // Read
    printerInput.read(currentMillis);
    externalVentilationSwitch.read();

    // Process
    enclosurePower.tick(currentMillis, printerInput.isOn());
    ledLighting.tick(currentMillis);
    ventilation.tick(currentMillis, externalVentilationSwitch.isOn(), printerInput.isOn());

    display_loop();

    // Write
    powerArduino.setState(enclosurePower.isPowerActive());
    powerLight.setState(ledLighting.isOn());
    powerEnclosure.setState(enclosurePower.isPowerActive());
    powerEnclosureVentilation.setState(ventilation.isEnclosureVentilationOn());
    powerExternalVentilation.setState(ventilation.isExternalVentilationReq());
}

// cppcheck-suppress unusedFunction
void shutdown(void)
{
    enclosurePower.setOff();
}
