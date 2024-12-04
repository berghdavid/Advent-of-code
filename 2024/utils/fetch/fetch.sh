#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <day>"
	echo "Example: $0 1"
    exit 1
fi

. ../.env
cp -r -n empty_day ../$1
make build && AOC_SESSION=$AOC_SESSION ./bin/main $1
