#!/bin/sh

app=$(realpath build/app/complex-dot)

run_test () {
	echo "Complex dot of" $2 "with"$3
	$app $1 $2 $3
	printf "\n"
}

cd ./tests

run_test 2 ./data/f1.txt ./data/f2.txt 
run_test 2 ./data/f1.txt ./data/f1.txt 
run_test 2 ./data/f2.txt ./data/f2.txt 

# returning so that the tests can be chained together
cd ..
