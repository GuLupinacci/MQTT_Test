# Technical test 

For this test, Raspberry Pi was chosen as the hardware due to my familiarity with other projects and also because of its resources such as ease of library installation and the presence of GPIO pins that allow direct interaction with external peripherals, in this case, the display. 

# Repository structure

This repository is organized as follows:

* src: project source files (.c).

* include: project header files (.h).

* test: folder containing unit tests.

* out: files generated during the compilation process.

* Makefile: compiles the source files and/or project tests.

* Script "build_and_run": a bash script that installs the necessary project libraries and then compiles, builds the program, and runs the programs.

# Used Libraries

## Mosquitto 
Need to set up the MQTT broker on localhost
```
sudo apt-get install mosquitto
```

## Paho mqtt 

Paho MQTT was chosen for its ease of use and robust support, allowing quick and reliable integration of MQTT communication.
```
git clone https://github.com/eclipse/paho.mqtt.c.git
cd paho.mqtt.c
make 
```

## WiringPi 
WiringPi was chosen due to its simplicity and effectiveness in handling Raspberry Pi GPIO pins, facilitating interaction with external electronic devices.
```
git clone https://github.com/WiringPi/WiringPi.git 
cd Wiringpi
./build
```

## Libjson 
Need to manipulate JSON data upon receiving the MQTT message.
```
sudo apt-get install libjson-c-dev
```

# Running the Programs

As requested, two programs are run in parallel to perform this task. The first one initializes communication with the 20x4 LCD display via GPIOs and then subscribes to the "localhost" broker on the "/test/trimble" topic. Upon receiving messages, it checks the content and writes to the display according to the presented rules. The second program publishes to the "/test/trimble" topic the runtime every 10 seconds.

The Makefile compiles both programs with the **make** command and runs them together with the **make run** command. Another option to run the programs is to use the script **./build_and_run.sh**, which executes the same commands but also installs the necessary libraries if they are missing.

# Tests

For unit tests, I created some simple functions to verify the execution sequence of each part of the project. To simulate a Raspberry Pi, I used a VirtualBox primarily for hardware communication tests.

