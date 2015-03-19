/* 
 * File:   TempPi.h
 * Project: Raspbrewer
 * Author: Blake Sutton
 * Email: blasutto@uat.edu
 *
 * Created on March 18, 2015, 6:55 PM
 */

#ifndef TEMPPI_H
#define	TEMPPI_H

class TempPi {
public:
    TempPi();
    TempPi(const TempPi& orig);
    virtual ~TempPi();
    
    void registerSensor(std::string);
private:

};

#endif	/* TEMPPI_H */

