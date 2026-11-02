# Project 4
This project is an implementation of a low pass filter

## Running
`./build/src/lowpass <coefficient a> <iteration_count> <file.wav>`
$$
    y_t = x_t + a x_{t-1}
$$

## Dependencies
- CMake
- C/C++ compiler with C++ 20 support

### For testing scripts
- UNIX system with bash

## Build Instructions
To create configure the cmake directory:
``bash
cmake -B build
``
To build the project:
``bash
cmake --build build
``
Then run the binaries generated in the `./build/` directory.
There are also some precompiled mac executables in the executables folder for your convenience.

## Text file numbers:
The accepted formats for the numbers are:
- $a + bi$
- $bi + a$
- $a$
- $bi$
- $a - bi$
- $-a + bi$
- $-a - bi$

Where $a, b \in R$
