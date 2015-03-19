/* 
 * File:   TempPi.cpp
 * Project: Raspbrewer
 * Author: Blake Sutton
 * Email: blasutto@uat.edu
 *
 * Created on March 18, 2015, 6:55 PM
 * Last Updated: 3/18/2015
 */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "TempPi.h"

TempPi::TempPi() {
    // Run two system commands to initialize the temperature sensors
    system("sudo modeprobe w1-gpio");
    system("sudo modeprobe w1-therm");
    
    path = "/sys/bus/w1/devices/";
    extension = "/w1_slave";
}

TempPi::TempPi(const TempPi& orig) {
}

TempPi::~TempPi() {
}

void TempPi::registerSensor(std::string name, std::string id) {
    sensors[name] = id;
    std::cout << "Registration of the sensor " << name << " was successful." << std::endl;
}

void TempPi::readTemp(std::string name) {
    std::ifstream file;
    std::string filename = path + sensors[name] + extension;
    std::string reading;
    
    file.open(filename.c_str());
    if(file.is_open()){
        while(!file.eof()) {
            reading.push_back(file.get());
        }
        file.close();        
    } else {
        std::cout << "Could not read from the sensor!" << std::endl;
    }
    int temp = atoi(reading.substr(reading.find("t=") + 2, reading.length()).c_str());
    
    std::cout << toCelsius(temp) << std::endl;
    std::cout << toFahrenheit(temp) << std::endl;
}

float TempPi::toCelsius(int temp) {
    return temp / 1000;
}

float TempPi::toFahrenheit(int temp) {
    return toCelsius(temp) * 9 / 5 + 32;
}