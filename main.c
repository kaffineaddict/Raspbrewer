/* 
 * File:   main.c
 * Project: Raspbrewer
 * Author: Blake Sutton
 * Email: blasutto@uat.edu
 *
 * Created on March 9, 2015, 9:07 PM
 * Last Updated: 3/17/2015
 */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <stdio.h>
#include <stdlib.h>
#include "relayPi.h"

int relay_1 = 0;
int relay_2 = 1;
int relay_3 = 2;
int relay_4 = 3;

/*
 * The main loop for the brewery
 */
int main(int argc, char** argv) {
    int a = initBrew();
    printf("%d\n", a);
    initRelay(relay_1);
    initRelay(relay_2);
    initRelay(relay_3);
    initRelay(relay_4);
    return (EXIT_SUCCESS);
}