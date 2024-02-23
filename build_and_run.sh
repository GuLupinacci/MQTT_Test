#!/bin/bash
if ! dpkg -s mosquitto >/dev/null 2>&1 ; then
    sudo apt-get install mosquitto
fi
if [ ! -d paho.mqtt.c ] ; then
    git clone https://github.com/eclipse/paho.mqtt.c.git
    cd paho.mqtt.c
    make 
    cd ..
fi
if [ ! -d WiringPi ] ; then
    git clone https://github.com/WiringPi/WiringPi.git 
    cd Wiringpi
    ./build
    cd ..
fi
if ! dpkg -s libjson-c-dev >/dev/null 2>&1 ; then
    sudo apt-get install libjson-c-dev
fi
make clean
make
make run