/* 
 * File:   TempPi.cpp
 * Project: Raspbrewer
 * Author: Blake Sutton
 * Email: blasutto@uat.edu
 *
 * Created on March 18, 2015, 6:55 PM
 */

#include "TempPi.h"

TempPi::TempPi() {
    // Run two system commands to initialize the temperature sensors
    system("sudo modeprobe w1-gpio");
    system("sudo modeprobe w1-therm");
}

TempPi::TempPi(const TempPi& orig) {
}

TempPi::~TempPi() {
}

TempPi::registerSensor(String id) {
    
}