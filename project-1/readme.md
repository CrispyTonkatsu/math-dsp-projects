# Project 1
This project is a simple complex number calculator.

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

## Testing script
Additionally, one can just run all the sample tests by doing `./tests/scripts/test-all.sh` on UNIX systems.

## Accepted strings:
The accepted formats for the numbers are:
- $a + bi$
- $bi + a$
- $a$
- $bi$
- $a - bi$
- $-a + bi$
- $-a - bi$

Where $a, b \in R$
