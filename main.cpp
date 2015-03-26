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
#include <pthread.h>
#include "RelayPi.h"
#include "TempPi.h"

using namespace std;

int relay_1 = 0; // pin 11
int relay_2 = 1; // pin 12
int relay_3 = 2; // pin 13
int relay_4 = 3; // pin 15
std::string sensor1 = "28-00000655b53a";
std::string beer_name = "Cream Ale";

pthread_t t1, t1_id, t2, t2_id;

void *testThread(void *);
void *testThread2(void *);
void buildScreen(int, int);
/*
 * 
 */
int main(int argc, char** argv) {
    RelayPi relay;
    TempPi temp;
    bool running = true;
    int count = 0;
    float main_temp = 0;
    float next_temp = 0;
    
    int row,col;                                 /* to store the number of rows and *
                                                /* the number of colums of the screen */
    initscr();                                  /* start the curses mode */
    getmaxyx(stdscr,row,col);                   /* get the number of rows and columns */
    
    temp.registerSensor("main_brew", "28-00000655b53a");
    temp.registerSensor("next_brew", "28-00000657dc06");
    
    pthread_create( &t2, NULL, testThread2, NULL);
    
    pthread_create( &t1, NULL, testThread, NULL);
    
    buildScreen(row, col);
    while(running)
    {   
        count++;
        main_temp = temp.readTemp("main_brew");
        next_temp = temp.readTemp("next_brew");
        mvprintw(LINES - 1, 0, "Frame: %d", count);     
        mvprintw(LINES - 2, col - 18, "Main Temp: %4.2f", main_temp);
        mvprintw(LINES - 1, col - 18, "Next Temp: %4.2f", next_temp);
        refresh();
        delay(250);
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
    mvprintw(LINES - 2, 0, "Brewing: %s", beer_name.c_str());
    mvprintw(LINES - 3, 0, "%s", bar.c_str());
}

void *testThread(void *ptr)
{
    //t1 =  pthread_self();
    while(true)
    {
        char c = getch();
        mvprintw(1, 0, "You Pressed: %c", c);
    }
    pthread_exit(NULL);
}

void *testThread2(void *ptr)
{
    RelayPi relay;
    TempPi temp;
    bool running = true;
    int count = 0;
    float main_temp = 0;
    float next_temp = 0;
    
    int row,col;                                 /* to store the number of rows and *
                                                /* the number of colums of the screen */
    initscr();                                  /* start the curses mode */
    getmaxyx(stdscr,row,col);                   /* get the number of rows and columns */
    
    temp.registerSensor("main_brew", "28-00000655b53a");
    temp.registerSensor("next_brew", "28-00000657dc06");
    
    buildScreen(row, col);
    while(running)
    {   
        count++;
        main_temp = temp.readTemp("main_brew");
        next_temp = temp.readTemp("next_brew");
        mvprintw(LINES - 1, 0, "Frame: %d", count);     
        mvprintw(LINES - 2, col - 18, "Main Temp: %4.2f", main_temp);
        mvprintw(LINES - 1, col - 18, "Next Temp: %4.2f", next_temp);
        refresh();
        delay(250);
    }
    pthread_exit(NULL);
}