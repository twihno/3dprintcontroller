#include "Relay.hpp"

Relay::Relay(unsigned int relay_pin, bool mode)
{
    pin = relay_pin;

    this->ON = mode;
    this->OFF = !mode;

    pinMode(pin, OUTPUT);
    init();
}

void Relay::init()
{
    this->state = 0;
    digitalWrite(this->pin, OFF);
}

void Relay::on()
{
    this->setState(1);
}

void Relay::off()
{
    this->setState(0);
}

void Relay::toggle()
{
    this->setState(!(this->state));
}

bool Relay::isOn()
{
    return this->getState();
}

void Relay::setState(bool desired_state)
{
    if (this->state != desired_state)
    {
        this->state = desired_state;
        if (state)
        {
            digitalWrite(this->pin, ON);
        }
        else
        {
            digitalWrite(this->pin, OFF);
        }
    }
}
