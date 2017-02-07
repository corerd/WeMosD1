WeMos D1 mini pro
=================

The D1 mini Pro is a mini wifi board based on ESP-8266EX.

![user input clear](https://corerd.github.io/WeMosD1/img/D1-mini-pro.jpg)

See [WeMos](https://www.wemos.cc/product/d1-mini-pro.html) official web site
for full documentation.


**Features**:

- 11 digital input/output pins
- Interrupt/pwm/I2C/one-wire
- 1 analog input(3.2V max input)
- 16M bytes(128M bit) Flash
- External antenna connector
- Built-in ceramic antenna
- New CP2104 USB-TO-UART IC
- Same size as D1 mini, but more light


Technical specs   ||
----------------- | ------------------:
Microcontroller   | ESP-8266EX
Operating Voltage | 3.3V
Digital I/O Pins  | 11
Analog Input Pins | 1(Max input: 3.2V)
Clock Speed       | 80MHz/160MHz
Flash             | 16M bytes
Length            | 34.2mm
Width             | 25.6mm
Weight            | 2.5g


Pin | Function                      | ESP-8266 Pin
--- | ----------------------------- | ------------
TX  | TXD                           | TXD
RX  | RXD                           | RXD
A0  | Analog input, max 3.3V input  | A0
D0  | IO                            | GPIO16
D1  | IO, SCL                       | GPIO5
D2  | IO, SDA                       | GPIO4
D3  | IO, 10k Pull-up               | GPIO0
D4  | IO, 10k Pull-up, BUILTIN_LED  | GPIO2
D5  | IO, SCK                       | GPIO14
D6  | IO, MISO                      | GPIO12
D7  | IO, MOSI                      | GPIO13
D8  | IO, 10k Pull-down, SS         | GPIO15
G   | Ground                        | GND
5V  | 5V                            | -
3V3 | 3.3V                          | 3.3V
RST | Reset                         | RST

All of the IO pins have interrupt/pwm/I2C/one-wire support except D0.

All of the IO pins run at 3.3V.



PlatformIO IDE
=============================
I choose [PlatformIO IDE](http://platformio.org/platformio-ide) as integrated development environment.

It is a cross-platform build system running on top of [GitHub's Atom](https://atom.io) text editor.

The repository directory structure complies with the need to maintain both the libraries and the projects source code.

Repository directory structure
------------------------------

    +--WeMosD1
    |  +--libraries
    |  |  +--_Lib_stub_
    |  |     +--src
    |  |        +- _Lib_stub_.c
    |  |        +- _Lib_stub_.h
    |  +--projects
    |  |  +--_App_stub_
    |  |  |  +--lib
    |  |  |  |  +- readme.txt
    |  |  |  +--src
    |  |  |  |  +- main.cpp
    |  |  |  +- platformio.ini
    |  |  +- platformio.ini.template


**./libraries**

Extra libraries directories root where PlatformIO Library Dependency Finder (LDF)
will look for dependencies.

Set `lib_extra_dirs` LDF option to libraries absolute path in platformio.ini
(see below).


**./libraries/\_Lib\_stub\_**

\_Lib\_stub\_ library directory root.


**./libraries/\_Lib\_stub\_/src**

Source code of \_Lib\_stub\_ library.


**./projects**

PlatformIO projects directories root.


**./projects/platformio.ini.template**

PlatformIO project configuration file template.

Update the project specific `platformio.ini` file with its content.


**./projects/\_App\_stub\_**

\_App\_stub\_ project directory root.


**./projects/\_App\_stub\_/src**

Source code of the project.

**./projects/\_App\_stub\_/lib**

This directory can be used to store the project specific (private) libraries.

More details are located in `lib/readme.txt` file.


**./projects/\_App\_stub\_/platformio.ini**

\_App\_stub\_ project configuration file.

This file is created any time that PlatformIO initializes a project.

Add the following lines to the `[env:d1_mini]` section:
```
; extra directory where Library Dependency Finder (LDF) will look for dependencies.
lib_extra_dirs = ../../libraries

; uploader connection speed (baud rate) used to send firmware to board.
upload_speed = 921600
```
See `platformio.ini.template`.


PlatformIO IDE Setup
--------------------

Launch Atom editor and add a project folder (i.e. WeMosD1):
```
File > "Add Project Folder..." > /path/to/WeMosD1
```

Create the directories:
```
./libraries
./libraries/_Lib_stub_
./projects
```

Create a PlatformIO project:
```
PlatformIO > "Initialize or Update PlatformIO Project"
```

The `PlatformIO: Initialize or Update PlatformIO Project` dialog should result:
```
Selected board:
WeMos D1 R2 & mini

Choose the directory:
/absolute/path/to/WeMosD1/projects/_App_stub_
```
