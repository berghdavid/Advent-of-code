#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <problem>"
	echo "Example: $0 2"
    exit 1
fi

day=${PWD##*/}

. ../utils/.env
if [[ $2 == "1" ]]; then
    make build_1 && AOC_SESSION=$AOC_SESSION ./bin/1 $day $2  < data/data.in
else
    make build_2 && AOC_SESSION=$AOC_SESSION ./bin/2 $day $2  < data/data.in
fi
