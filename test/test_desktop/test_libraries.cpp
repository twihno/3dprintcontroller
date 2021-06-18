#include <stdint.h>
#include <ArduinoFake.h>
#include <unity.h>

#include "Relay.hpp"
#include "PullupInput.hpp"
#include "LEDLighting.hpp"
#include "EnclosurePower.hpp"

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
}

void test_pullupinput(void)
{
    When(Method(ArduinoFake(), pinMode)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalRead)).AlwaysReturn(1);

    PullupInput pullinput = PullupInput(13);
}

void test_enclosurepower(void)
{
    EnclosurePower enclosurePower;
    
    // Initially enclosurePower is required to be off
    TEST_ASSERT_FALSE(enclosurePower.isOn());
    
    // Test if we can turn on enclosurePower
    enclosurePower.setOn(0);
    TEST_ASSERT_TRUE(enclosurePower.isOn());

    // Test if we can turn off enclosurePower
    enclosurePower.setOff();
    TEST_ASSERT_FALSE(enclosurePower.isOn());
    
    // Test if enclosurePower turns off after timeout has been reached and autoOff is enabled
    enclosurePower.enableAutoOff();
    enclosurePower.setOn(0);
    enclosurePower.tick(100);
    TEST_ASSERT_TRUE(enclosurePower.isOn());
    enclosurePower.tick(10000);
    TEST_ASSERT_TRUE(enclosurePower.isOn());
    enclosurePower.tick(10001);
    TEST_ASSERT_FALSE(enclosurePower.isOn());

    // Test if enclosurePower stays on after timeout has been reached and autoOff is disabled
    enclosurePower.disableAutoOff();
    enclosurePower.setOn(0);
    enclosurePower.tick(100);
    TEST_ASSERT_TRUE(enclosurePower.isOn());
    enclosurePower.tick(10000);
    TEST_ASSERT_TRUE(enclosurePower.isOn());
    enclosurePower.tick(10001);
    TEST_ASSERT_TRUE(enclosurePower.isOn());
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
    ledLighting.tick(100);
    TEST_ASSERT_TRUE(ledLighting.isOn());
    ledLighting.tick(10000);
    TEST_ASSERT_TRUE(ledLighting.isOn());
    ledLighting.tick(10001);
    TEST_ASSERT_FALSE(ledLighting.isOn());
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_setup);
    RUN_TEST(test_relay);
    RUN_TEST(test_pullupinput);
    RUN_TEST(test_enclosurepower);
    RUN_TEST(test_ledlighting);

    UNITY_END();

    return 0;
}
