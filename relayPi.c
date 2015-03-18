/* 
 * File:   relayPi.c
 * Project: Raspbrewer
 * Author: Blake Sutton
 * Email: blasutto@uat.edu
 *
 * Created on March 11, 2015, 8:57 PM
 * Last Updated: 3/17/2015
 */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <wiringPi.h>
#include <stdio.h>

int initBrew(void) {
    if(wiringPiSetup() == -1){ 
        printf("setup wiringPi failed !\n");
        return 0;
    }
    return 1; 
}

void initRelay(int pin) {
    printf("Setting up relay pin on wiringPi pin: %d\n", pin);
    pinMode(pin, OUTPUT);
}