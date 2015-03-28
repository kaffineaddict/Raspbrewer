/* 
 * File:   TempPi.cpp
 * Project: Raspbrewer
 * Author: Blake Sutton
 * Email: blasutto@uat.edu
 *
 * Created on March 18, 2015, 6:55 PM
 * Last Updated: 3/27/2015
 */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "TempPi.h"

/**
 * Create the object and run the root commands to
 * load the correct modules for the temperature sensors.
 */
TempPi::TempPi() {
    // Run two system commands to initialize the temperature sensors
    system("sudo modprobe w1-gpio");
    system("sudo modprobe w1-therm");
    
    path = "/sys/bus/w1/devices/";
    extension = "/w1_slave";
}

TempPi::TempPi(const TempPi& orig) {
}

TempPi::~TempPi() {
}

/**
 * Register a sensor but the ID
 * 
 * @param name A human readable name of the sensor
 * @param id The unique ID associated with the sensor
 */
void TempPi::registerSensor(std::string name, std::string id) {
    sensors[name] = id;
}

/**
 * This function takes the sensors human readable name and returns the temperature
 * value.
 * @param name The human readable name of a registered sensor
 * @return The temperature in Fahrenheit
 */
float TempPi::readTemp(std::string name) {
    std::ifstream file;
    std::string filename = path + sensors[name] + extension;
    std::string reading;
    
    // open the file where it stores the last reading
    file.open(filename.c_str());
    if(file.is_open()){
        while(!file.eof()) {
            // read the last line.
            reading.push_back(file.get());
        }
        file.close();        
    } else {
        std::cout << "Could not read from the sensor!" << std::endl;
    }
    // convert the string to an integer to get the temp value
    int temp = atoi(reading.substr(reading.find("t=") + 2, reading.length()).c_str());

    return toFahrenheit(temp);
}

/**
 * Convert the one wire value to Celsius and return it.
 * @param temp The integer value read from a one wire sensor
 * @return The temperature in Celsius
 */
float TempPi::toCelsius(int temp) {
    return temp / 1000;
}

/**
 * Convert the one wire value to Fahrenheit and return it.
 * @param temp The integer value read from a one wire sensor
 * @return The temperature in Fahrenheit
 */
float TempPi::toFahrenheit(int temp) {
    return toCelsius(temp) * 9 / 5 + 32;
}