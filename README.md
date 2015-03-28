# Raspbrewer
#####Author: Blake Sutton
#####Email:  blasutto@uat.edu
#####Class: CSC323 - Raspberry Pi

###Overview:
Raspbrewer is designed to be a simple and easily modified automated home brewery control powered by the Raspberry Pi.

###Demonstration
[Demonstration Video](https://youtu.be/usqvsCGNW-Y)

###Users/Audience:
 * Homebrewers
 * Programers
 * Tinkerers

This project is aimed at any tech savvy individuals who want to get into home brewing or are looking to help others automate their home brewing process. It is NOT intended for commercial purposes as there are much stricter stipulations and regulations in place. This project is available under the Mozilla Public License.

###Setup:
The newer raspian images do not have the correct settings in the config. You must add the following line to your boot config if it is not present.
```shell
dtoverlay=w1-gpio
```

[Wiring the SainSmart](http://theswivelchair.net/2015/03/powering-relays-relay-input/)

[Wiring the Outlet](http://theswivelchair.net/2015/03/powering-relays-relay-output/)

###Running:
Simply run the following through a terminal or ssh.
```shell
sudo ./raspbrewer
```

###Prior Work and Libraries:
 * [WiringPi](http://wiringpi.com) - Raspberry Pi GPIO library for C
 * [PThread](https://www.sourceware.org/pthreads-win32/manual/) - Multithreading C library
 * [NCurses](http://www.gnu.org/software/ncurses/ncurses.html) - Terminal GUI control
