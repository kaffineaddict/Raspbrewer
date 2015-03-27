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
#include <ctime>
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
int stage = 0;
const std::string stages[] = {"Mash", "Lautering", "Boiling", "Done"};
std::string beer_name = "Cream Ale";

pthread_t temp_thread, main_thread, input_thread;

void *updateTemperature(void *);
void *getInput(void *);
void *mainLoop(void *);
void buildScreen(int, int);

/*
 * The main function to enter the brew loops
 */
int main(int argc, char** argv) {   
    pthread_create( &temp_thread, NULL, updateTemperature, NULL);
    pthread_create( &input_thread, NULL, getInput, NULL);
    pthread_create( &main_thread, NULL, mainLoop, NULL);
    pthread_join(input_thread,  NULL);
    endwin();
    return 0;
}

void buildScreen(int rows, int cols)
{
    std::string bar = std::string(cols, '=');
    mvprintw(LINES - 6, 0, "%s", bar.c_str());
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
        } else if(c == 27) {
            echo();
            pthread_exit(NULL);
        }else {
            input += c;
        }
    }
    pthread_exit(NULL);
}

void *mainLoop(void *ptr)
{
    time_t begin, now;
    double minutes;
    begin = time(NULL);
  
    RelayPi relay;
    relay.initBrew();
    relay.initRelay("Pump 1", relay_1);
    relay.initRelay("Pump 2", relay_2);
    relay.initRelay("Pump 3", relay_3);
    relay.initRelay("Pump 4", relay_4);
    relay.updateRelay("Pump 1", relay.RELAYPI_ON);
    
    bool running = true;
    
    int row,col;                                 /* to store the number of rows and *
                                                /* the number of colums of the screen */
    initscr();                                  /* start the curses mode */
    getmaxyx(stdscr,row,col);                   /* get the number of rows and columns */   
    buildScreen(row, col);
    while(running)
    {   
        now = time(NULL);
        minutes = difftime(now,begin) / 60;
        move(1, 0);
        clrtoeol(); 
        mvprintw(1, 0, "Command: %s", input.c_str());
        mvprintw(LINES - 5, 0, "Relay 1: %s", relay.getState("Pump 1").c_str());
        mvprintw(LINES - 4, 0, "Relay 2: %s", relay.getState("Pump 2").c_str());
        mvprintw(LINES - 5, COLS - 12, "Relay 3: %s", relay.getState("Pump 3").c_str());
        mvprintw(LINES - 4, COLS - 12, "Relay 4: %s", relay.getState("Pump 4").c_str());
        mvprintw(LINES - 7, 0, "Time: %4.2f", minutes);
        mvprintw(LINES - 1, 0, "Stage: %s", stages[stage].c_str());     
        mvprintw(LINES - 2, col - 26, "Main Temp: %4.2f", main_temp);
        mvprintw(LINES - 1, col - 26, "Boiler Temp: %4.2f", second_temp);
        refresh();
        delay(250);
    }
    pthread_exit(NULL);
}