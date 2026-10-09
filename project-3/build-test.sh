#!/bin/sh

rm -rf ./build
cmake -B build
cmake --build build

./build/src/bitrev-app 16 > out16.txt
diff out16.txt ./test-data/out16.txt

./build/src/bitrev-app 32 > out32.txt
diff out32.txt ./test-data/out32.txt

echo "Test results located in current directory"
