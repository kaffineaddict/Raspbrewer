/* 
 * File:   RelayPi.cpp
 * Project: Raspbrewer
 * Author: Blake Sutton
 * Email: blasutto@uat.edu
 *
 * Created on March 17, 2015, 7:41 PM
 * Last Updated: 3/18/2015
 */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "RelayPi.h"

RelayPi::RelayPi() {
    RELAYPI_ON = true;
    RELAYPI_OFF = false;
}

RelayPi::RelayPi(const RelayPi& orig) {
}

RelayPi::~RelayPi() {
}

bool RelayPi::initBrew(void) {
    if (wiringPiSetup() == -1) {
        std::cout << "Setup of wiringPi failed !" << std::endl;
        return true;
    }
    return false;
}

void RelayPi::initRelay(std::string name, int pin) {
    std::cout << "Setting up " << name << " relay on wiringPi pin: " << pin << std::endl;
    pinMode(pin, OUTPUT); // wiringPi pin method to change GPIO state
    relays[name] = pin;
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
    return updateRelay(pin, state);
}