/* 
 * File:   main.c
 * Author: Blake Sutton
 * Email: blasutto@uat.edu
 *
 * Created on March 9, 2015, 9:07 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "relayPi.h"

int relay_1 = 0;
int relay_2 = 1;
int relay_3 = 2;
int relay_4 = 3;

/*
 * The main loop for the brewery
 */
int main(int argc, char** argv) {
    int a = initBrew();
    printf("%d\n", a);
    initRelay(relay_1);
    initRelay(relay_2);
    initRelay(relay_3);
    initRelay(relay_4);
    return (EXIT_SUCCESS);
}