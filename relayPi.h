/* 
 * File:   relayPi.h
 * Project: Raspbrewer
 * Author: Blake Sutton
 * Email: blasutto@uat.edu
 *
 * Created on March 11, 2015, 8:57 PM
 * Last Updated: 3/17/2015
 */
#ifndef RELAYPI_H
#define	RELAYPI_H

#ifdef	__cplusplus
extern "C" {
#endif

extern int initBrew(void);
extern void initRelay(int);

#ifdef	__cplusplus
}
#endif

#endif	/* RELAYPI_H */