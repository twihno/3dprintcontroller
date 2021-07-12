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
#include "CachedPullupInput.hpp"

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

void test_main(void)
{

}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_main);

    UNITY_END();

    return 0;
}
