#include <stdint.h>
#include <ArduinoFake.h>
#include <unity.h>

#include "Constants.hpp"

#include "Relay.hpp"
#include "PullupInput.hpp"
#include "LEDLighting.hpp"
#include "EnclosurePower.hpp"
#include "Ventilation.hpp"
#include "PrinterInput.hpp"

using namespace fakeit;

void test_setup(void)
{
    When(Method(ArduinoFake(), pinMode)).Return();
    When(Method(ArduinoFake(), digitalWrite)).Return();
    When(Method(ArduinoFake(), digitalRead)).Return();

    setUp();
}

void setUp(void)
{
    ArduinoFakeReset();
}

void test_relay(void)
{
    When(Method(ArduinoFake(), pinMode)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalRead)).AlwaysReturn(1);

    Relay r = Relay(13, LOW);

    // Initially a relay is required to be off
    TEST_ASSERT_FALSE(r.isOn());

    // Test if we can turn on the relay
    r.on();
    TEST_ASSERT_TRUE(r.isOn());

    // Test if we can turn off the relay
    r.off();
    TEST_ASSERT_FALSE(r.isOn());

    // Test if we can toggle the relay
    r.toggle();
    TEST_ASSERT_TRUE(r.isOn());
    r.toggle();
    TEST_ASSERT_FALSE(r.isOn());
    r.toggle();
    r.toggle();
    TEST_ASSERT_FALSE(r.isOn());
}

void test_pullupinput(void)
{
    When(Method(ArduinoFake(), pinMode)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalRead)).Return(1, 0, 1, 0);

    PullupInput pullinput = PullupInput(13);

    TEST_ASSERT_FALSE(pullinput.isOn());
    TEST_ASSERT_TRUE(pullinput.isOn());

    TEST_ASSERT_TRUE(pullinput.isOff());
    TEST_ASSERT_FALSE(pullinput.isOff());
}

void test_printerinput(void)
{
    When(Method(ArduinoFake(), pinMode)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalRead)).Return(0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1);

    PrinterInput printerInput = PrinterInput(13);

    TEST_ASSERT_FALSE(printerInput.isOn());

    // Check timeout fail during startup
    printerInput.read(0);
    TEST_ASSERT_FALSE(printerInput.isOn());

    printerInput.read(PRINTER_ON_TOLERANCE);
    TEST_ASSERT_FALSE(printerInput.isOn());

    printerInput.read(PRINTER_ON_TOLERANCE + 1);
    TEST_ASSERT_FALSE(printerInput.isOn());

    // Check timeout success during startup
    printerInput.read(0);
    TEST_ASSERT_FALSE(printerInput.isOn());

    printerInput.read(PRINTER_ON_TOLERANCE);
    TEST_ASSERT_FALSE(printerInput.isOn());

    printerInput.read(PRINTER_ON_TOLERANCE + 1);
    TEST_ASSERT_TRUE(printerInput.isOn());

    // Check timeout fail during shutdown
    printerInput.read(0);
    TEST_ASSERT_TRUE(printerInput.isOn());

    printerInput.read(PRINTER_OFF_TOLERANCE);
    TEST_ASSERT_TRUE(printerInput.isOn());
    
    printerInput.read(PRINTER_OFF_TOLERANCE + 1);
    TEST_ASSERT_TRUE(printerInput.isOn());

    // Check timeout success during shutdown
    printerInput.read(0);
    TEST_ASSERT_TRUE(printerInput.isOn());

    printerInput.read(PRINTER_OFF_TOLERANCE);
    TEST_ASSERT_TRUE(printerInput.isOn());

    printerInput.read(PRINTER_OFF_TOLERANCE + 1);
    TEST_ASSERT_FALSE(printerInput.isOn());
}

void test_enclosurepower_auto_off(void)
{
    EnclosurePower enclosurePower;

    TEST_ASSERT_TRUE(enclosurePower.isAutoOff())

    // Initially enclosurePower is required to be off
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test if we can turn on enclosurePower
    enclosurePower.setOn();
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test if we can turn off enclosurePower
    enclosurePower.setOff();
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test if enclosurePower doesn't change its state
    enclosurePower.setOff();
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    enclosurePower.abort();
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    enclosurePower.tick(0, true);
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    enclosurePower.tick(0, false);
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Turn on enclosurePower
    enclosurePower.setOn();
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test if enclosurePower doesn't change its state
    enclosurePower.setOn();
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    enclosurePower.abort();
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    enclosurePower.tick(0, false);
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test if printer startup is detected
    enclosurePower.tick(0, true);
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_TRUE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test if enclosurePower doesn't change its state
    enclosurePower.setOn();
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_TRUE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    enclosurePower.abort();
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_TRUE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test if setOff() works when the printer is running
    enclosurePower.setOff();
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test if shutdown triggers
    enclosurePower.setOn();
    enclosurePower.tick(0, true);
    TEST_ASSERT_TRUE(enclosurePower.isAutoOff())

    enclosurePower.tick(0, false);
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_TRUE(enclosurePower.isShutdown());

    // Test abort by isPrinterOn
    enclosurePower.tick(0, true);
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_TRUE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test abort function
    enclosurePower.tick(0, false);
    enclosurePower.abort();
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test setOn() during shutdown
    enclosurePower.tick(0, true);
    enclosurePower.tick(0, false);
    enclosurePower.setOn();
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test setOff() during shutdown
    enclosurePower.tick(0, true);
    enclosurePower.tick(0, false);
    enclosurePower.setOff();
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test timer shutdown
    enclosurePower.setOn();
    enclosurePower.tick(0, true);
    enclosurePower.tick(0, false);

    enclosurePower.tick(ENCLOSUREPOWER_TIMEOUT - 1, false);
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_TRUE(enclosurePower.isShutdown());

    enclosurePower.tick(ENCLOSUREPOWER_TIMEOUT, false);
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_TRUE(enclosurePower.isShutdown());

    enclosurePower.tick(ENCLOSUREPOWER_TIMEOUT + 1, false);
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    uint32_t currentMillis = 1000;

    // Test getShutdownTimer
    enclosurePower.setOn();
    enclosurePower.tick(currentMillis, true);
    enclosurePower.tick(currentMillis, false);
    TEST_ASSERT_TRUE(enclosurePower.getShutdownTimer(currentMillis) == ENCLOSUREPOWER_TIMEOUT);

    currentMillis += ENCLOSUREPOWER_TIMEOUT - 1;
    enclosurePower.tick(currentMillis, false);
    TEST_ASSERT_TRUE(enclosurePower.getShutdownTimer(currentMillis) == 1);

    currentMillis++;
    enclosurePower.tick(currentMillis, false);
    TEST_ASSERT_TRUE(enclosurePower.getShutdownTimer(currentMillis) == 0);

    currentMillis++;
    enclosurePower.tick(currentMillis, false);
    TEST_ASSERT_TRUE(enclosurePower.getShutdownTimer(currentMillis) == 0);
}

void test_enclosurepower_copycat(void)
{
    EnclosurePower enclosurePower;

    // Initially enclosurePower is required to be off
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Turn off autoOff
    enclosurePower.disableAutoOff();
    TEST_ASSERT_FALSE(enclosurePower.isAutoOff())

    // Test if we can turn on enclosurePower
    enclosurePower.setOn();
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test if we can turn off enclosurePower
    enclosurePower.setOff();
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test if enclosurePower doesn't change its state
    enclosurePower.setOff();
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    enclosurePower.abort();
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    enclosurePower.tick(0, true);
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    enclosurePower.tick(0, false);
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Turn on enclosurePower
    enclosurePower.setOn();
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test if enclosurePower doesn't change its state
    enclosurePower.setOn();
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    enclosurePower.abort();
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    enclosurePower.tick(0, false);
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test if printer startup is detected
    enclosurePower.tick(0, true);
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_TRUE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test if enclosurePower doesn't change its state
    enclosurePower.setOn();
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_TRUE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    enclosurePower.abort();
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_TRUE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test if setOff() works when the printer is running
    enclosurePower.setOff();
    TEST_ASSERT_FALSE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());

    // Test if printer standby is detected
    enclosurePower.setOn();
    enclosurePower.tick(0, true);
    TEST_ASSERT_FALSE(enclosurePower.isAutoOff())

    enclosurePower.tick(0, false);
    TEST_ASSERT_TRUE(enclosurePower.isPowerActive());
    TEST_ASSERT_FALSE(enclosurePower.isPrinterRunning());
    TEST_ASSERT_FALSE(enclosurePower.isShutdown());
}

void test_ventilation(void)
{
    Ventilation ventilation = Ventilation();

    // Test initial state
    TEST_ASSERT_FALSE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_FALSE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_FALSE(ventilation.isShutdown());

    // Test recursive transitions
    ventilation.tick(0, false, false);
    TEST_ASSERT_FALSE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_FALSE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_FALSE(ventilation.isShutdown());

    ventilation.tick(0, true, false);
    TEST_ASSERT_FALSE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_FALSE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_FALSE(ventilation.isShutdown());

    ventilation.tick(0, false, false);
    TEST_ASSERT_FALSE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_FALSE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_FALSE(ventilation.isShutdown());

    // Test transition from OFF to ON
    ventilation.tick(0, false, true);
    TEST_ASSERT_TRUE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_TRUE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_FALSE(ventilation.isShutdown());

    // Test recursive transitions
    ventilation.tick(0, false, true);
    TEST_ASSERT_TRUE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_TRUE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_FALSE(ventilation.isShutdown());

    ventilation.tick(0, true, true);
    TEST_ASSERT_TRUE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_FALSE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_FALSE(ventilation.isShutdown());

    ventilation.tick(0, false, true);
    TEST_ASSERT_TRUE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_TRUE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_FALSE(ventilation.isShutdown());

    // Test transition from ON to SHUTDOWN
    ventilation.tick(0, false, false);
    TEST_ASSERT_TRUE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_TRUE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_TRUE(ventilation.isShutdown());

    // Test recursive transitions
    ventilation.tick(0, false, false);
    TEST_ASSERT_TRUE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_TRUE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_TRUE(ventilation.isShutdown());

    ventilation.tick(0, true, false);
    TEST_ASSERT_TRUE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_FALSE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_TRUE(ventilation.isShutdown());

    ventilation.tick(0, false, false);
    TEST_ASSERT_TRUE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_TRUE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_TRUE(ventilation.isShutdown());

    // Test transition from SHUTDOWN to ON
    ventilation.tick(0, false, true);
    TEST_ASSERT_TRUE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_TRUE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_FALSE(ventilation.isShutdown());

    // Test shutdown timer
    ventilation.tick(0, false, false);
    TEST_ASSERT_TRUE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_TRUE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_TRUE(ventilation.isShutdown());

    ventilation.tick(ENCLOSUREVENTILATION_TIMEOUT - 1, false, false);
    TEST_ASSERT_TRUE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_TRUE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_TRUE(ventilation.isShutdown());

    ventilation.tick(ENCLOSUREVENTILATION_TIMEOUT, false, false);
    TEST_ASSERT_TRUE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_TRUE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_TRUE(ventilation.isShutdown());

    ventilation.tick(ENCLOSUREVENTILATION_TIMEOUT + 1, false, false);
    TEST_ASSERT_FALSE(ventilation.isEnclosureVentilationOn());
    TEST_ASSERT_FALSE(ventilation.isExternalVentilationReq());
    TEST_ASSERT_FALSE(ventilation.isShutdown());
}

void test_ledlighting(void)
{
    LEDLighting ledLighting;
    
    // Initially ledLighting is required to be off
    TEST_ASSERT_FALSE(ledLighting.isOn());
    
    // Test if we can turn on ledLighting
    ledLighting.setOn(0);
    TEST_ASSERT_TRUE(ledLighting.isOn());

    // Test if we can turn off ledLighting
    ledLighting.setOff();
    TEST_ASSERT_FALSE(ledLighting.isOn());
    
    // Test if ledLighting turns off after timeout has been reached
    ledLighting.setOn(0);
    ledLighting.tick(LEDLIGHTING_TIMEOUT - 1);
    TEST_ASSERT_TRUE(ledLighting.isOn());
    ledLighting.tick(LEDLIGHTING_TIMEOUT);
    TEST_ASSERT_TRUE(ledLighting.isOn());
    ledLighting.tick(LEDLIGHTING_TIMEOUT + 1);
    TEST_ASSERT_FALSE(ledLighting.isOn());
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_setup);
    RUN_TEST(test_relay);
    RUN_TEST(test_pullupinput);
    RUN_TEST(test_printerinput);
    RUN_TEST(test_enclosurepower_auto_off);
    RUN_TEST(test_enclosurepower_copycat);
    RUN_TEST(test_ventilation);
    RUN_TEST(test_ledlighting);

    UNITY_END();

    return 0;
}
