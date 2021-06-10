#include <stdint.h>
#include <ArduinoFake.h>
#include <unity.h>

#include "Relay.hpp"
#include "PullupInput.hpp"

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

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_setup);
    RUN_TEST(test_relay);
    RUN_TEST(test_pullupinput);

    UNITY_END(); // stop unit testing

    return 0;
}
