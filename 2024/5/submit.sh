#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <day> <problem>"
	echo "Example: $0 17 2"
    exit 1
fi

. ../utils/.env
if [[ $2 == "1" ]]; then
    make build_1 && AOC_SESSION=$AOC_SESSION ./bin/1 $1 $2  < data/data.in
else
    make build_2 && AOC_SESSION=$AOC_SESSION ./bin/2 $1 $2  < data/data.in
fi
