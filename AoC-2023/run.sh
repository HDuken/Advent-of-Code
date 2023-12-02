#!/bin/bash

clear
g++ -Wall -DPART"$2"=true "$1".cpp -o out &&
./out < "$1".txt &&
rm -f out
