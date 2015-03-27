/* 
 * File:   RelayPi.h
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

#include <wiringPi.h>
#include <iostream>
#include <map>

#ifndef RELAYPI_H
#define	RELAYPI_H

class RelayPi {
public:
    RelayPi();
    RelayPi(const RelayPi& orig);
    virtual ~RelayPi();
    
    bool initBrew(void);
    void initRelay(std::string, int);
    void updateRelay(int, bool);
    void updateRelay(std::string, bool);
    std::string getState(std::string);
    
    // static flags for relays
    bool RELAYPI_ON;
    bool RELAYPI_OFF;
private:
    // a private list of the relays and a name to access them
    std::map<std::string, int> relays;
    std::map<std::string, bool> relay_state;
};

#endif	/* RELAYPI_H */