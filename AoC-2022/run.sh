#!/bin/bash
# https://adventofcode.com/2022/

clear
g++ -Wall   day17/sol.cpp -o out
./out <     day17/day17.txt
# ./out <     test.txt
rm -f out
