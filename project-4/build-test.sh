#!/bin/sh

rm -rf ./build
cmake -B build
cmake --build build

./build/src/bitrev-app 16 > out16.txt
diff out16.txt ./test-data/out16.txt

./build/src/bitrev-app 32 > out32.txt
diff out32.txt ./test-data/out32.txt

./build/src/br-fft-app 8 ./test-data/input1.txt > output1.txt
./build/src/br-fft-app 8 ./test-data/input2.txt > output2.txt

./build/src/benchmark

echo "Test results located in current directory"
