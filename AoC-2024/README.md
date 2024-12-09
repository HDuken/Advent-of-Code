# Advent of Code

<div align="center">
    <img src="https://img.shields.io/badge/Stars%20⭐-18/50-yellow">
</div>

![aoc2024](aoc2024.png)

## Day 9

- For part 1, use two-pointer method
- For part 2, setup two arrays including the size and starting indices of free spaces and files.

## Day 8

- Simple math operations for 2D poses.

## Day 7

- Maintain a set to store temporary values
- Iterate over all value in the array: Temporary values are all possible values from doing all possible operations between all previous temporary values with the current value

## Day 6

- Put obstacles on all visited positions in part 1.
- Pure brute force on all possible obstacle positions
- Detect the loop when a position is already visited, the same position with the same moving direction.
  - Use a 3D `boolean` array. The first two dimensions correspond to the dimension of the map

## Day 5

- Not much to say, for each update, iterate over all rules
  - Skip irrelevant rules, in which both components are not present
- For part 2, save the list of related rules, in which both components are present
  - Sort the array with insertion sort by swapping element

## Day 4

It's so easy that I don't know what to write here. Just a bunch of if-else statements are enough `:))`

## Day 3

- Finally learn how to use `regex`
- The `don't` flag doesn't reset by the end of each line, which sucks by the way.
- Simply put everything in a single line to avoid coming up with another solution

## Day 2

- Instead of going with overly complicate if-else conditions, just brute force the heck out of it.

## Day 1

- Simple operation on 2 arrays, simply sort them first
- For the second half, use two pointers method. Not sure if needed, but surely a bit faster.
