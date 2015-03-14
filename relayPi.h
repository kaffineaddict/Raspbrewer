/* 
 * File:   relayPi.h
 * Author: KaffineAddict
 *
 * Created on March 11, 2015, 8:57 PM
 */

#ifndef RELAYPI_H
#define	RELAYPI_H

#ifdef	__cplusplus
extern "C" {
#endif

extern void relayPrint(void);
extern int initBrew(void);
extern void initRelay(int);

#ifdef	__cplusplus
}
#endif

#endif	/* RELAYPI_H */

