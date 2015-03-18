/* 
 * File:   main.cpp
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

#include <iostream>
#include "RelayPi.h"
#include <unistd.h>

using namespace std;

int relay_1 = 0;
int relay_2 = 1;
int relay_3 = 2;
int relay_4 = 3;

/*
 * 
 */
int main(int argc, char** argv) {
    RelayPi relay;
    relay.initBrew();
    cout << "The relay has been activated. Initializing..." << endl;
    relay.initRelay(relay_1);
    relay.initRelay(relay_2);
    relay.initRelay(relay_3);
    relay.initRelay(relay_4);
    usleep(10000 * 1000);
    relay.updateRelay(relay_1, true);
    usleep(10000 * 1000);
    relay.updateRelay(relay_1, false);
    return 0;
}