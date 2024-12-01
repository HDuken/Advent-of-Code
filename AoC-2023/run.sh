#!/bin/bash

clear
echo "Advent of Code 2023 | Day $1 Part $2:"

if [ ! -e $1.cpp ]; then
    echo "Initialize Day $1"
    cp temp.cpp $1.cpp
    touch "$1"real.txt "$1"exam.ex
    exit
fi

g++ -DPART"$2"=true "$1".cpp -DDEBUG="$3" -o out &&
./out < "$1".txt &&
rm -f out
