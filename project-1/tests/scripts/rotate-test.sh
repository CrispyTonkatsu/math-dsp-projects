#!/bin/sh

app=$(realpath build/app/rotate)

run_test () {
	echo "Rotate" $2 "by angle 2*PI*"$3
	$app $1 $2 $3
	printf "\n"
}

cd ./tests

run_test 2 ./data/f1.txt 0
run_test 2 ./data/f1.txt 0.25
run_test 2 ./data/f1.txt -0.25
run_test 2 ./data/f1.txt 0.75
run_test 2 ./data/f1.txt 0.5

run_test 2 ./data/f2.txt 0.25
run_test 2 ./data/f2.txt -0.25
run_test 2 ./data/f2.txt 0.75
run_test 2 ./data/f2.txt 0.5

# returning so that the tests can be chained together
cd ..
