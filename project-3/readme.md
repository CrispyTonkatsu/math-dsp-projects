# Project 3
This project is an implementation of bit reversal FFT and a benchmark of the DFT algorithms.

## Running
`./build/src/bitrev-app ${N}`
Where $N = 2^k$.

`./build/src/br-fft-app ${N} ${numbers file}`
Where the numbers file is a file of N complex numbers.

`./build/src/benchmark`
The timing.txt will be placed in the current directory.

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
