#!/bin/sh

rm -rf ./build
cmake -B build
cmake --build build

echo "Testing DFT"
./build/src/dft-calc 8 ./test-data/input1.txt > dft-out-1.txt
diff dft-out-1.txt ./test-data/output1.txt

./build/src/dft-calc 8 ./test-data/input2.txt > dft-out-2.txt
diff dft-out-2.txt ./test-data/output2.txt

echo "Testing FFT"
./build/src/fft-calc 8 ./test-data/input1.txt > fft-out-1.txt
diff fft-out-1.txt ./test-data/output1.txt

./build/src/fft-calc 8 ./test-data/input2.txt > fft-out-2.txt
diff fft-out-2.txt ./test-data/output2.txt

echo "Test results located in current directory"
