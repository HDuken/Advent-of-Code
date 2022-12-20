<!-- omit in toc -->
# Advent-of-Code

My solutions for [Advent of Code 2022](https://adventofcode.com/2022).

Other solutions, cool visualizations can also be found at [reddit/adventofcode](https://www.reddit.com/r/adventofcode/)

<!-- omit in toc -->
## Table of Contents

- [Day 1](#day-1)
- [Day 2](#day-2)
- [Day 3](#day-3)
- [Day 4](#day-4)
- [Day 5](#day-5)
- [Day 6](#day-6)
- [Day 7](#day-7)
- [Day 8](#day-8)
- [Day 9](#day-9)

-------

## Day 1

Part 1:

- The problem is about simply reading the input and taking the sum of values
- We only need to find the maximum value, thus there is no need to store the calories each Elf carrying, just the current one and the maximum.
- What left is checking for blank line and EOF (end of file). For this, use `std::ifstream` and `string.empty()`

Part 2:

- For this part, simply extend a single maximum value to an array of 3 maximum values.
- If the current sum is greater than the minimum of the 3 values, we update the array.

-------

## Day 2

Part 1:

- Assign values as follows:
  - Player 1: Rock (A) = 0, Paper (B) = 1, Scissor (C) = 2 (`P1 - 'A'`)
  - Player 2: Rock (X) = 2, Paper (Y) = 1, Scissor (Z) = 0 (`2 - (P2 - 'X')`)
- You will see that the result of a round can be identified from `(P1 + P2) MOD 3`
  - `(P1 + P2) MOD 3 == 1`: win
  - `(P1 + P2) MOD 3 == 2`: draw
  - `(P1 + P2) MOD 3 == 0`: lost

Part 2:

- The hand of player 2 can be identified by `(R - P1 + 3) MOD 3`
- Assign values as follows to have a slightly nicer result mod
  - Player 1: Rock (A) = 1, Paper (B) = 0, Scissor (C) = 2 (`(1 - (P1 - 'A')) MOD 3`)
  - Player 2: Rock (X) = 0, Paper (Y) = 1, Scissor (Z) = 2
  - `(P1 + P2) MOD 3 == 2`: win
  - `(P1 + P2) MOD 3 == 1`: draw
  - `(P1 + P2) MOD 3 == 0`: lost

-------

## Day 3

Part 1:

- Simply keep an array of size 53 to check whether each alphabet char is present in each half string.
- If a char is present in both half string, add the *priority* to the result
- Use `std::string_view` to reduce storage

Part 2:

- Basically similar to part 1, now with 3 strings.

-------

## Day 4

Part 1:

- After reading the input, simply compare the range lower and upper bounds:
  - Range 1 contains range 2 if:
    $$lower\_bound_1 ≤ lower\_bound_2 \land upper\_bound_1 ≥ upper\_bound_2$$
  - Range 2 contains range 1 if:
    $$lower\_bound_1 ≥ lower\_bound_2 \land upper\_bound_1 ≤ upper\_bound_2$$

Part 2:

- There will be no overlap if either of the following happens
  - $lower\_bound_2 > upper\_bound_1$
  - $lower\_bound_1 > upper\_bound_2$

-------

## Day 5

- Due to input format, reading the stack orders was a bit annoying.
- It's easier to specify the number of crate stacks in the beginning as a constant
- Reading the moving sequences and implementing it were rather simple with vector's `insert` and `erase`.
- Part 2 is similar to part 1, only minor changes is needed for `insert` and `erase` methods.

-------

## Day 6

- Store the latest N characters in an array
- Have a function to check if all characters in that array is unique
  - Brute force comparison in $\mathcal{O}(N^2)$ would be fine, since there are only 4-p14 chars
  - Alternatively, we can create a $26 \times 1$ array to keep the presence of each alphabet char
- With that, keep reading characters and increment the count until all characters are unique.

-------

## Day 7

Part 1:

Part 2:

-------

## Day 8

Part 1:

- Scan in each direction, check each tree one by one
- Compare the current height with the maximum height of checked trees, if the current height is greater, it's visible, else it's not visible.
- The final visibility is the OR of the visibility from 4 directions (though in implementation, simply assign value to one single 2D array)

Part 2:

- The view at each tree is independent with the view of its neighbors. Thus, must have a function to get the view from each position and check the *scenic score* at every possible positions
- Though it's $\mathcal{O}(N^2)$, the map is small enough to go brute force like this.
- Possible speed up with multi-threading, but it's not a must.

-------

## Day 9

Part 1:

- The position of the head $x_{head}, y_{head}$ can be easily computed from the move commands
- If the position of the current tail is no longer "close" to the head, update it. The new position is always next to the position of the new head, on the opposite direction of the movement.
- Collect these positions into a trajectory. The movement pattern is rather simple, move diagonally one if needed, than basically just either horizontally or vertically.

Part 2: things are getting fun now

- The movement is much more complicated to just have a trajectory of few key points
- Instead, simulate the whole movement, one step at a time
