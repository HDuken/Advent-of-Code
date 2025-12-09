#!/bin/bash

clear
echo "Advent of Code 2025 | Day $1:"

if [ ! -e $1.cpp ]; then
    echo "Initialize Day $1"
    cp temp.cpp $1.cpp
    touch $1.txt
    exit
fi

# g++ -DPART?=true "$1".cpp -o out -Winvalid-pch -H &&
# ./out <test.txt &&

echo "Part 1:"
g++ -DPART1=true "$1".cpp -o out -Winvalid-pch &&
    time ./out <"$1".txt && rm -f out

echo "Part 2:"
g++ -DPART2=true "$1".cpp -o out -Winvalid-pch &&
    time ./out <"$1".txt && rm -f out
