#!/bin/bash

clear
echo "Advent of Code 2023 | Day $1 Part $2:"
g++ -DPART"$2"=true "$1".cpp -o out &&
./out < "$1".txt &&
rm -f out
