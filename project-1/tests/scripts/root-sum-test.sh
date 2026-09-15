#!/bin/sh

app=$(realpath build/app/root-sum)

run_test () {
	echo "Unity root sum with N="$1 "K="$2
	$app $1 $2
	printf "\n"
}

cd ./tests

run_test 4 2
run_test 3 2
run_test 8 7

# returning so that the tests can be chained together
cd ..
