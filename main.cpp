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
#include "TempPi.h"

using namespace std;

int relay_1 = 0; // pin 11
int relay_2 = 1; // pin 12
int relay_3 = 2; // pin 13
int relay_4 = 3; // pin 15
std::string sensor1 = "28-00000655b53a";

/*
 * 
 */
int main(int argc, char** argv) {
    RelayPi relay;
    TempPi temp;
    
    relay.initBrew();
    cout << "The relay has been activated. Initializing..." << endl;
    relay.initRelay("Port1", relay_1);
    relay.initRelay("Port2", relay_2);
    relay.initRelay("Port3", relay_3);
    relay.initRelay("Port4", relay_4);
    temp.registerSensor("main_brew", "28-00000655b53a");
    temp.registerSensor("second_brew", "28-00000657dc06");
    temp.readTemp("main_brew");
    temp.readTemp("second_brew");
    return 0;
}