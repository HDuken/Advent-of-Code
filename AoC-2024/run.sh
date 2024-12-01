#!/bin/bash

clear
echo "Advent of Code 2024 | Day $1 Part $2:"

if [ ! -e $1.cpp ]; then
    echo "Initialize Day $1"
    cp temp.cpp $1.cpp
    touch $1.txt
    exit
fi

g++ -DPART"$2"=true "$1".cpp -o out -Winvalid-pch -H &&
    ./out <"$1".txt &&
    rm -f out
