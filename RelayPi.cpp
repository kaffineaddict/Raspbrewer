/* 
 * File:   RelayPi.cpp
 * Project: Raspbrewer
 * Author: Blake Sutton
 * Email: blasutto@uat.edu
 *
 * Created on March 17, 2015, 7:41 PM
 * Last Updated: 3/17/2015
 */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "RelayPi.h"

RelayPi::RelayPi() {
}

RelayPi::RelayPi(const RelayPi& orig) {
}

RelayPi::~RelayPi() {
}

bool RelayPi::initBrew(void) {
    if (wiringPiSetup() == -1) {
        printf("setup wiringPi failed !\n");
        return true;
    }
    return false;
}

void RelayPi::initRelay(int pin) {
    printf("Setting up relay pin on wiringPi pin: %d\n", pin);
    pinMode(pin, OUTPUT);
}

void RelayPi::updateRelay(int pin, bool state) {
    if(state) {
        digitalWrite(pin, HIGH);
    } else {
        digitalWrite(pin, LOW); 
    }
}
