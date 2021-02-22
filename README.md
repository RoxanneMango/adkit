# adkit [![build status](https://github.com/RoxanneMango/adkit/actions/workflows/c-cpp.yml/badge.svg?branch=main)](https://github.com/RoxanneMango/adkit/actions/workflows/c-cpp.yml)
Developer toolchain for the arduino due

### Contains the following components:
- arm-none-eabi cross-compiler for the SAM3X CPU -- version 9.3.1-2020q2
- Flash programmer for Atmel SAM devices for the command-line (BOSSAC) -- version 1.6.2-arduino
- Port bump python script
- Example project in the src directory

### Requires the following dependencies:
- Python 3
- GCC supporting at least c++11
- tar
- curl
- make

### Contains the following libraries:
- Arduino Core for SAM3X CPU
- Arduino library for controlling single-wire-based LED pixels
- RTC Library for the Arduino Due (real time clock)
- Catch2 unit testing framework for C++, single include version
