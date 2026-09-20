# Project 1
This project is a simple complex number calculator.

## Dependencies
- CMake
- Clang version with C++ 20 support

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

## Arguments
### rotate
`rotate ${number_count} ${number_file} ${angle_multiplier}`

### root-sum
`root-sum ${nth_root} ${k_root_count}`

### complex-dot
`complex-dot ${number_count} ${vector_a_file} ${vector_b_file}`

### unity-dot
`unity-dot ${number_count} ${number_file}`

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
