#!/bin/sh

rm -rf ./build
cmake -B build
cmake --build build

for file in ./test-data/*; do
	if [ -f "$file" ]; then
		./format_match.sh "$file" "mono-$file"
		./build/src/lowpass "0.2" "10" "mono-$file"
	fi
done

echo "Program outputs located in current directory"
