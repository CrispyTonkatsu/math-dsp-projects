#!/bin/sh

rm -rf ./build
cmake -B build
cmake --build build

for file in ./test-data/*; do
	if [ -f "$file" ]; then
		./format_match.sh "$file" "output.wav"
		./build/src/lowpass "0.2" "10000" "filtered-output.wav"
	fi
done

echo "Program outputs located in current directory"
