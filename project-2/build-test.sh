#!/bin/sh

rm -rf ./build
cmake -B build
cmake --build build

rm out.txt
./tests/scripts/test-all.sh >> out.txt
echo "Test results located in out.txt"
