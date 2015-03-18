/* 
 * File:   RelayPi.h
 * Author: KaffineAddict
 *
 * Created on March 17, 2015, 7:41 PM
 */

#include <wiringPi.h>
#include <stdio.h>

#ifndef RELAYPI_H
#define	RELAYPI_H

class RelayPi {
public:
    RelayPi();
    RelayPi(const RelayPi& orig);
    virtual ~RelayPi();
    
    bool initBrew(void);
    void initRelay(int);
    void updateRelay(int, bool);
private:

};

#endif	/* RELAYPI_H */