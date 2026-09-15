#!/bin/sh

app=$(realpath build/app/unity-dot)

run_test () {
	echo "Unity dot product of N="$1 "with file" $2
	$app $1 $2
	printf "\n"
}

cd ./tests

run_test 2 ./data/f1.txt
run_test 2 ./data/f2.txt

# returning so that the tests can be chained together
cd ..
