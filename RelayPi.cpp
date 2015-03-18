/* 
 * File:   RelayPi.cpp
 * Author: KaffineAddict
 * 
 * Created on March 17, 2015, 7:41 PM
 */

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