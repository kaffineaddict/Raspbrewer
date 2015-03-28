/* 
 * File:   RelayPi.cpp
 * Project: Raspbrewer
 * Author: Blake Sutton
 * Email: blasutto@uat.edu
 *
 * Created on March 17, 2015, 7:41 PM
 * Last Updated: 3/23/2015
 */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "RelayPi.h"

/**
 * A constructor with initialization of the two relay flags.
 */
RelayPi::RelayPi() {
    RELAYPI_ON = true;
    RELAYPI_OFF = false;
}

RelayPi::RelayPi(const RelayPi& orig) {
}

/**
 * Unused destructor at this time.
 */
RelayPi::~RelayPi() {
}

/**
 * Initialize a relay with a human readable name.
 * @param name A string name for the relay that can be used to update it.
 * @param pin The WiringPi number of the pin we want to use.
 */
void RelayPi::initRelay(std::string name, int pin) {
    pinMode(pin, OUTPUT); // wiringPi pin method to change GPIO state
    relays[name] = pin;
    digitalWrite(pin, HIGH);
}

/**
 * This function is used to switch the relay on and off.
 * Activate a relay using true and deactivate with false.
 * 
 * @param pin The wiringPi pin number to talk through.
 * @param state The desired state of the relay (RELAYPI_ON, RELAYPI_OFF)
 */
void RelayPi::updateRelay(int pin, bool state) {
    if(state) {
        digitalWrite(pin, LOW); // low activates the relay
    } else {
        digitalWrite(pin, HIGH); 
    }
}

/**
 * Allows us to activate a relay by name.
 * 
 * @param name The assigned name for the relay
 * @param state The desired state of the relay (RELAYPI_ON, RELAYPI_OFF)
 */
void RelayPi::updateRelay(std::string name, bool state) {
    int pin = relays[name];
    relay_state[name] = state;
    return updateRelay(pin, state);
}

/**
 * Allows us to activate a relay by name.
 * 
 * @param name The assigned name for the relay
 * @param state The desired state of the relay (RELAYPI_ON, RELAYPI_OFF)
 */
std::string RelayPi::getState(std::string name) {
    return relay_state[name] ? "On" : "Off";
}