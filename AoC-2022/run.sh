#!/bin/bash
# https://adventofcode.com/2022/

clear
g++ -Wall   day24/day24-p1.cpp -o out
./out <     day24/day24.txt
# ./out <     test.txt
rm -f out
