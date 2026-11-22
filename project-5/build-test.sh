#!/bin/sh

rm -rf ./build
cmake -B build
cmake --build build

for file in ./test-data/*; do
	if [ -f "$file" ]; then
		./format_match.sh "$file" "audio.wav"
		./build/src/lowpass "0.2" "1000" "audio.wav"
	fi
done

echo "Program outputs located in current directory"
