#!/bin/bash
# https://adventofcode.com/2022/

clear
g++ -Wall   day9-p2.cpp -o out
./out <     day9.txt
# ./out <     test.txt
rm -f out
