#!/bin/sh

rm -rf ./build
cmake -B build
cmake --build build

./build/src/pluck "220"

echo "Program outputs located in current directory"
