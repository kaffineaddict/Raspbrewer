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

int relay_1 = 0; // pin 11
int relay_2 = 1; // pin 12
int relay_3 = 2; // pin 13
int relay_4 = 3; // pin 15

float main_temp, second_temp;
std::string input;
std::string main_sensor = "28-00000655b53a";
std::string second_sensor = "28-00000657dc06";
const std::string stages[] = {"Mash", "Lautering", "Boiling", "Done"};
std::string beer_name = "Cream Ale";

pthread_t temp_thread, print_thread, input_thread;

void *updateTemperature(void *);
void *getInput(void *);
void *updateScreen(void *);
void buildScreen(int, int);

/*
 * The main function to enter the brew loops
 */
int main(int argc, char** argv) {   
    pthread_create( &temp_thread, NULL, updateTemperature, NULL);
    pthread_create( &input_thread, NULL, getInput, NULL);
    pthread_create( &print_thread, NULL, updateScreen, NULL);
    pthread_join(print_thread,  NULL);
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
    mvprintw(LINES - 3, 0, "%s", bar.c_str());
    mvprintw(LINES - 2, 0, "Brewing: %s", beer_name.c_str());    
}

void *updateTemperature(void *ptr)
{
    TempPi temp;
    temp.registerSensor("main_brew", "28-00000655b53a");
    temp.registerSensor("boiling_water", "28-00000657dc06");
    while(1)
    {
        main_temp = temp.readTemp("main_brew");
        second_temp = temp.readTemp("boiling_water");
    }
}

void *getInput(void *ptr)
{
    noecho();
    keypad(stdscr, TRUE);
    while(true)
    {
        int c = getch();
        if(c == KEY_BACKSPACE)
        {
            input = input.substr(0, input.length() - 1);            
        } else {
            input += c;
        }
    }
    pthread_exit(NULL);
}

void *updateScreen(void *ptr)
{
    RelayPi relay;
    bool running = true;
    int count = 0;
    
    int row,col;                                 /* to store the number of rows and *
                                                /* the number of colums of the screen */
    initscr();                                  /* start the curses mode */
    getmaxyx(stdscr,row,col);                   /* get the number of rows and columns */   
    buildScreen(row, col);
    while(running)
    {   
        count++;
        move(1, 0);
        clrtoeol(); 
        mvprintw(1, 0, "Command: %s", input.c_str());
        mvprintw(LINES - 1, 0, "Frame: %d", count);     
        mvprintw(LINES - 2, col - 26, "Main Temp: %4.2f", main_temp);
        mvprintw(LINES - 1, col - 26, "Boiler Temp: %4.2f", second_temp);
        refresh();
        delay(250);
    }
    pthread_exit(NULL);
}