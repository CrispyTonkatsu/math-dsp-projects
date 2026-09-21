# Project 2
This project is an implementation of the DFT and the FFT algorithms

## Running
`./build/src/dft-calc ${N} ${numbers file}`
`./build/src/fft-calc ${N} ${numbers file}`
Where the numbers file is a file of N complex numbers.

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

## Testing script
Additionally, one can just run all the sample tests by doing `./tests/scripts/test-all.sh` on UNIX systems.

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
