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

/**
 * A high and low temp for the stage as well as the
 * time in minutes to maintain.
 */
struct brew_range {
    float low, high;
    double length;
};


// A list of all possible relays
int relay_1 = 0; // pin 11
int relay_2 = 1; // pin 12
int relay_3 = 2; // pin 13
int relay_4 = 3; // pin 15

// Two brew temperature holding variables
float main_temp, second_temp;

// A list of all sensors I have attached and their ID
std::string main_sensor   = "28-000006577ca5";
std::string second_sensor = "28-00000657041d";

// This will track what stage we are working on.
int stage = 0;

// Holds the current status message
std::string status;

// An array of all the human readable brew stages.
const std::string stages[] = {"Mash-In", "Mash-Out", "Lautering", "Boiling", "Done"};

// A name for the current brew.
std::string beer_name = "Cream Ale";

// Two temperature control structures.
brew_range mash_range, boil_range;

// A variable to hold the boiling temperature of water.
const double boiling = 212;

// A list of our three threads
pthread_t temp_thread, main_thread, input_thread;

// Get a handle to the relay controls
RelayPi relay;

// Two time holding variables to track stage progress.
time_t begin, now;
// A variable to hold the time difference in minutes.
double minutes;

// The headers for the functions 
bool temperatureControl(brew_range);
void *updateTemperature(void *);
void *getInput(void *);
void *mainLoop(void *);
void buildScreen(int, int);
bool initBrew(void);

/*
 * The main function to start our three threads.
 */
int main(int argc, char** argv) { 
    initBrew();
    // A thread to monitor our temperature sensors.
    pthread_create(&temp_thread, NULL, updateTemperature, NULL);
    // A thread to monitor input to close out when esc is pressed.
    pthread_create(&input_thread, NULL, getInput, NULL);
    // A thread to control the flow
    pthread_create(&main_thread, NULL, mainLoop, NULL);
    // Make sure we dont exit until the main loop does.
    pthread_join(main_thread, NULL);
    endwin(); // clean up the ncurses window
    return 0;
}

/**
 * Build the screen and layout a basic box and pattern.
 * 
 * @param rows The screen row size
 * @param cols The screen column size
 */
void buildScreen(int rows, int cols) {
    // fill a string with an = for each column
    std::string bar = std::string(cols, '=');
    // Move to a location and print
    mvprintw(LINES - 6, 0, "%s", bar.c_str());
    mvprintw(LINES - 3, 0, "%s", bar.c_str());
    mvprintw(LINES - 2, 0, "Brewing: %s", beer_name.c_str());
}

/**
 * A loop to read the current temperature and then update the variables
 */
void *updateTemperature(void *ptr) {
    // A handle to the temperature module
    TempPi temp;
    // register our two sensors
    temp.registerSensor("main_brew", main_sensor);
    temp.registerSensor("boiling_water", second_sensor);
    // Loop and read endlessly
    while (1) {
        main_temp = temp.readTemp("main_brew");
        second_temp = temp.readTemp("boiling_water");
    }
}

/**
 * A loop that looks for input. This is used during one stage to monitor
 * the user status and at all times to escape the program.
 */
void *getInput(void *ptr) {
    // turn off printing input.
    noecho();
    // capture all keys
    keypad(stdscr, TRUE);
    int c;
    // get the next char and exit if escape was pressed
    while((c = getch()) != 27) {
        // this checks if we are in the waiting on user stage
        if (stage == 2) {
            // we are done recirculating                
            stage++;
            begin = time(NULL);
            status = "Beginning the boil!";
        }
    }
    // cause the program to exit.
    stage = 10;
}

/**
 * This is the main loop. It prints to the screen and controls the flow 
 * of the process. 
 */
void *mainLoop(void *ptr) {      
    // startup the relay
    relay.initRelay("Pump 1", relay_1);
    relay.initRelay("Pump 2", relay_2);
    relay.initRelay("Pump 3", relay_3);
    relay.initRelay("Pump 4", relay_4);
    
    // 145-150 would be normal these are for testing
    // Setup the range for mashing
    mash_range.high = 80;
    mash_range.low = 75;
    mash_range.length = 1;

    // Setup the range for boiling
    boil_range.high = boiling + 5;
    boil_range.low = boiling;
    boil_range.length = 1.5;
    
    // setup ncurses screen
    initscr();
    // call our layout setup
    buildScreen(LINES, COLS);
    status = "Beginning Mash-In";
    // get current time 
    begin = time(NULL);
    while(true) {
        switch (stage) {
            case 0:
                // call our temperature monitoring program
                if(temperatureControl(mash_range)) {
                    status = "Heating up for the Mash-Out";                    
                }
                break;
            case 1:
                // normally would be 178
                if (main_temp > 100) {                    
                    status = "Awaiting any key press to signal for Lautering Complete.";
                    relay.updateRelay("Pump 1", relay.RELAYPI_OFF);
                    stage++;
                } else {
                    relay.updateRelay("Pump 1", relay.RELAYPI_ON);
                }
                break;
            case 2:
                // do nothing we are waiting on keypress                
                break;
            case 3:
                if(temperatureControl(boil_range)) {
                    delay(500);
                    status = "Done boiling. Shutting Down";
                    delay(5000);
                    echo();
                    pthread_exit(NULL);
                }
                break;
            default:
                echo();
                pthread_exit(NULL);
        }
        move(1, 0);         
        clrtoeol();
        move(LINES - 5, 0);
        clrtoeol();
        move(LINES - 4, 0);
        clrtoeol();        
        move(LINES - 1, 0);
        clrtoeol();
        
        mvprintw(1, 0, "Status: %s", status.c_str());
        mvprintw(LINES - 5, 0, "Relay 1: %s", relay.getState("Pump 1").c_str());
        mvprintw(LINES - 4, 0, "Relay 2: %s", relay.getState("Pump 2").c_str());
        mvprintw(LINES - 5, COLS - 12, "Relay 3: %s", relay.getState("Pump 3").c_str());
        mvprintw(LINES - 4, COLS - 12, "Relay 4: %s", relay.getState("Pump 4").c_str());
        mvprintw(LINES - 7, 0, "Time: %4.2f", minutes);
        mvprintw(LINES - 1, 0, "Stage: %s", stages[stage].c_str());
        mvprintw(LINES - 2, COLS - 26, "Main Temp: %4.2f", main_temp);
        mvprintw(LINES - 1, COLS - 26, "Boiler Temp: %4.2f", second_temp);
        refresh();
        delay(100); // give the cpu some free time
    }
    pthread_exit(NULL);
}

bool temperatureControl(brew_range data) {   
    now = time(NULL);
    minutes = difftime(now, begin) / 60;
    if (main_temp > data.high) {
        relay.updateRelay("Pump 1", relay.RELAYPI_OFF);
    }
    if (main_temp < data.low) {
        relay.updateRelay("Pump 1", relay.RELAYPI_ON);
    }
    if (minutes > data.length) {
        relay.updateRelay("Pump 1", relay.RELAYPI_OFF);
        stage++;        
        return true;
    }
    return false;
}

/**
 * Starts up and initializes the Raspberry Pi's GPIO
 * ports for use by the program.
 * 
 * @return True upon successful setup and false upon error.
 */
bool initBrew(void) {
    // call the wiring pi setup function
    if (wiringPiSetup() == -1) {
        std::cout << "Setup of wiringPi failed !" << std::endl;
        return true;
    }
    return false;
}