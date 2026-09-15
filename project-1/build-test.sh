#!/bin/sh

rm -rf ./build
cmake -B build
cmake --build build

./tests/scripts/test-all.sh >> out.txt
echo "Test results located in out.txt"
