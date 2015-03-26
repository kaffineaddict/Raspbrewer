/* 
 * File:   main.cpp
 * Project: Raspbrewer
 * Author: Blake Sutton
 * Email: blasutto@uat.edu
 *
 * Created on March 9, 2015, 9:07 PM
 * Last Updated: 3/25/2015
 */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <iostream>
#include <string.h>
#include <ncurses.h>
#include "RelayPi.h"
#include "TempPi.h"

using namespace std;

int relay_1 = 0; // pin 11
int relay_2 = 1; // pin 12
int relay_3 = 2; // pin 13
int relay_4 = 3; // pin 15
std::string sensor1 = "28-00000655b53a";

void buildScreen(int, int);
/*
 * 
 */
int main(int argc, char** argv) {
    RelayPi relay;
    TempPi temp;
    bool running = true;
    int count = 0;
    char mesg[]="Just a string";		/* message to be appeared on the screen */
    int row,col;				/* to store the number of rows and *
                                                /* the number of colums of the screen */
    initscr();                                  /* start the curses mode */
    getmaxyx(stdscr,row,col);                   /* get the number of rows and columns */
    //mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
    buildScreen(row, col);
    while(running)
    {
        mvprintw(LINES - 1, 0, "Frame: %d", count);
        refresh();
        delay(250);
        count++;
    }
    /**
    relay.initBrew();
    relay.initRelay("Port4", relay_4);
    relay.updateRelay(relay_4, relay.RELAYPI_OFF);
    temp.registerSensor("main_brew", "28-00000655b53a");
    temp.registerSensor("second_brew", "28-00000657dc06");
    temp.readTemp("main_brew");
    temp.readTemp("second_brew");
     * */
    endwin();
    return 0;
}

void buildScreen(int rows, int cols)
{
    std::string bar = std::string(cols, '=');
    mvprintw(LINES - 3, 0, "%s", bar);
}