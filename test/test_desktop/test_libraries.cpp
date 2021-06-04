#include <unity.h>

#include "Relay.hpp"
#include "PullupInput.hpp"

void test_relay(void)
{
    Relay r = Relay(13, LOW);
}

void test_pullupinput(void)
{
    PullupInput pullinput = PullupInput(13);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_relay);
    RUN_TEST(test_pullupinput);

    UNITY_END(); // stop unit testing

    return 0;
}
