#ifndef RELAY_HPP_INCLUDED
#define RELAY_HPP_INCLUDED

#include <Arduino.h>
#include <stdint.h>

class Relay
{
private:
    bool state;       //current state of the relay: 0: off; 1: on
    uint8_t pin;      //relay pin

    bool ON;  //physical relay state: on.
    bool OFF; //physical relay state: off.

    void init();

    void setState(bool desired_state); //Sets the relay state.

public:
    Relay(uint8_t relay_pin, //Arduino pin that the Relay is connected to
          bool mode          //Logic mode (default: high-active, i.e. high level means on).
    );

    void on(); //Turns the relay on.

    void off(); //Turns the relay off.

    void toggle(); //Toggles the relay state.

    bool isOn(); //Returns True if the relay is on.
};

#endif
