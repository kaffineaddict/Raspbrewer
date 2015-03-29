# Raspbrewer
#####Author: Blake Sutton
#####Email:  blasutto@uat.edu
#####Class: CSC323 - Raspberry Pi

###Overview:
Raspbrewer is designed to be a simple and easily modified automated home brewery control powered by the Raspberry Pi.

###License:
Raspbrewer is licensed under the MPL 2.0 license [Copy Found Here](https://github.com/KaffineAddict/Raspbrewer/blob/master/LICENSE)

This simply means your can use the code and keep your changes private. If you modify the Raspbrewer files you must share the source of those files.

###Demonstration
[Demonstration Video](https://youtu.be/usqvsCGNW-Y)

###Users/Audience:
 * Homebrewers
 * Programers
 * Tinkerers

This project is aimed at any tech savvy individuals who want to get into home brewing or are looking to help others automate their home brewing process. It is NOT intended for commercial purposes as there are much stricter stipulations and regulations in place. This project is available under the Mozilla Public License.

###Components Used:
 * [SainSmart 4 Channel Relay](http://www.amazon.com/gp/product/B0057OC5O8/ref=oh_aui_detailpage_o02_s00?ie=UTF8&psc=1)
 * [5- Pack WaterProof Temperature Sensors](http://www.amazon.com/gp/product/B00EU70ZL8/ref=oh_aui_detailpage_o02_s00?ie=UTF8&psc=1)
 * [Multi-Pack Resistors (a single 4.7k will work)](http://www.amazon.com/gp/product/B00E9Z0OCG/ref=oh_aui_detailpage_o02_s00?ie=UTF8&psc=1)
 

###Setup:
The newer raspian images do not have the correct settings in the config. You must add the following line to your boot config if it is not present.
```shell
dtoverlay=w1-gpio
```

You will also have to install WiringPi library. The library is at the bottom but here is a direct link to the install instructions. [HERE](http://wiringpi.com/download-and-install/)

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
