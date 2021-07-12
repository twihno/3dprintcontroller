#include <Arduino.h>
#include <unity.h>

#include "Relay.hpp"
#include "Ventilation.hpp"
#include "Constants.hpp"

void test_relay(void)
{
    Relay r = Relay(39, LOW);

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

void test_all_relays(void)
{
    Relay r[] = {
        Relay(23, LOW),
        Relay(25, LOW),
        Relay(27, LOW),
        Relay(29, LOW),
        Relay(31, LOW),
        Relay(33, LOW),
        Relay(35, LOW),
    };

    for (int i = 0; i < 7; i++)
    {
        // Test if Relay is off
        //TEST_ASSERT_EQUAL(digitalRead((i * 2) + 23), LOW);

        // Test turn on relay
        r[i].on();
        //TEST_ASSERT_EQUAL(digitalRead((i * 2) + 23), HIGH);

        delay(500);

        r[i].off();
        //TEST_ASSERT_EQUAL(digitalRead((i * 2) + 23), LOW);

        delay(100);
    }
}

void test_ventilation(void)
{
    Ventilation ventilation = Ventilation();

    Relay powerEnclosureVentilation = Relay(33, LOW);
    Relay powerExternalVentilation = Relay(35, LOW);

    bool printerOn = false;
    bool switchOn = false;

    //Tes initial state
    TEST_ASSERT_FALSE(powerEnclosureVentilation.isOn());
    TEST_ASSERT_FALSE(powerExternalVentilation.isOn());

    //Test initial state
    ventilation.tick(0, switchOn, printerOn);

    powerEnclosureVentilation.setState(ventilation.isEnclosureVentilationOn());
    powerExternalVentilation.setState(ventilation.isExternalVentilationReq());

    TEST_ASSERT_FALSE(powerEnclosureVentilation.isOn());
    TEST_ASSERT_FALSE(powerExternalVentilation.isOn());

    //Test printer on
    printerOn = true;

    ventilation.tick(1, switchOn, printerOn);

    powerEnclosureVentilation.setState(ventilation.isEnclosureVentilationOn());
    powerExternalVentilation.setState(ventilation.isExternalVentilationReq());

    TEST_ASSERT_TRUE(powerEnclosureVentilation.isOn());
    TEST_ASSERT_TRUE(powerExternalVentilation.isOn());

    //Test voodoo oszillatio

    for (int i = 0; i < 20; i++)
    {

        ventilation.tick(2 + i, switchOn, printerOn);

        powerEnclosureVentilation.setState(ventilation.isEnclosureVentilationOn());
        powerExternalVentilation.setState(ventilation.isExternalVentilationReq());

        delay(100);
    }

    //Test external ventilation on
    switchOn = true;

    ventilation.tick(100, switchOn, printerOn);

    powerEnclosureVentilation.setState(ventilation.isEnclosureVentilationOn());
    powerExternalVentilation.setState(ventilation.isExternalVentilationReq());

    TEST_ASSERT_TRUE(powerEnclosureVentilation.isOn());
    TEST_ASSERT_FALSE(powerExternalVentilation.isOn());

    //Test voodoo oszillatio

    for (int i = 0; i < 20; i++)
    {

        ventilation.tick(101 + i, switchOn, printerOn);

        powerEnclosureVentilation.setState(ventilation.isEnclosureVentilationOn());
        powerExternalVentilation.setState(ventilation.isExternalVentilationReq());

        delay(100);
    }
}

Relay powerArduino = Relay(37, LOW);

void setup()
{
    powerArduino.on();

    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_relay);
    RUN_TEST(test_all_relays);
    RUN_TEST(test_ventilation);
    UNITY_END();
}

void loop()
{
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}
