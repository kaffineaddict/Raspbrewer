/* 
 * File:   TempPi.h
 * Project: Raspbrewer
 * Author: Blake Sutton
 * Email: blasutto@uat.edu
 *
 * Created on March 18, 2015, 6:55 PM
 */

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <wiringPi.h>

#ifndef TEMPPI_H
#define	TEMPPI_H

class TempPi {
public:
    TempPi();
    TempPi(const TempPi& orig);
    virtual ~TempPi();
    
    void registerSensor(std::string, std::string);
    void readTemp(std::string);
private:
    float toCelsius(int temp);
    float toFahrenheit(int temp);
    std::map<std::string, std::string> sensors;
    std::string path;
    std::string extension;
};

#endif	/* TEMPPI_H */