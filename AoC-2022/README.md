<!-- omit in toc -->
# Advent-of-Code

My solutions for [Advent of Code 2022](https://adventofcode.com/2022).

<!-- omit in toc -->
## Table of Contents

- [Day 1](#day-1)
  - [Part 1](#part-1)
  - [Part 2](#part-2)
- [Day 2](#day-2)

-------

## Day 1

### Part 1

- The problem is about simply reading the input and taking the sum of values
- We only need to find the maximum value, thus there is no need to store the calories each Elf carrying, just the current one and the maximum.
- What left is checking for blank line and EOF (end of file). For this, use `std::ifstream` and `string.empty()`

### Part 2

- For this part, simply extend a single maximum value to an array of 3 maximum values.
- If the current sum is greater than the minimum of the 3 values, we update the array.

-------

## Day 2
