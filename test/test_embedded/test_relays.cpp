#include <Arduino.h>
#include <unity.h>

#include "Relay.hpp"

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
        TEST_ASSERT_FALSE(digitalRead((i * 2) + 23));

        // Test turn on relay
        r[i].on();
        TEST_ASSERT_TRUE(digitalRead((i * 2) + 23));

        delay(2000);

        r[i].off();
        TEST_ASSERT_FALSE(digitalRead((i * 2) + 23));

        delay(2000);
    }
}

Relay powerArduino = Relay(37, LOW);

void setup()
{
    powerArduino.on();

    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_relay);
    UNITY_END();
}

void loop()
{
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}
