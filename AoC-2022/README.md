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
- [Day 10](#day-10)
- [Day 11](#day-11)
- [Day 12](#day-12)
- [Day 13](#day-13)
- [Day 14](#day-14)
- [Day 15](#day-15)
- [Day 18](#day-18)

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

Create the following `struct File` and `Dir` for `class FileTree`:

```cpp
using LL = long long;

struct File
{
    string name_;
    LL size_;
    File(const string &name, const LL &size)
    : name_(name), size_(size) {};
};

struct Dir
{
    string name_;
    LL size_;
    Dir* parent_;
    vector<Dir*> subdirs_;
    vector<File*> files_;

    Dir(const string &name, const LL &size, Dir* parent)
    : name_(name), size_(size), parent_(parent) {};

    void add_file(const string &name, const LL &s);
    void add_dir(const string &name);
    Dir* cd_subdir(const string &name);
};

class FileTree
{
private:
    Dir *root_;

public:
    FileTree() : root_(new Dir("/", 0, nullptr)) {};
};
```

We can iterate down each tree with a `static private` method taking in pointer `Dir*`, and a public method calling that on `root_`

For example, to add the size of files to a directory:

```cpp
void FileTree::propagate_size(Dir *dir) {
    LL size = 0;
    for (auto file : dir->files_) {
        size += file->size_;
    }
    for (auto subdir : dir->subdirs_) {
        propagate_size(subdir);
        size += subdir->size_;
    }
    dir->size_ = size;
}

void FileTree::propagate_size() {
    propagate_size(root_);
}

```

Part 1: Go down the tree and add the size of `dirs` to a variable `sum`

```cpp
void FileTree::sum_size(Dir *dir, LL &sum);

void FileTree::sum_size(LL &sum) const {
    sum_size(root_, sum);
}
```

Part 2: similarly, go down the tree searching for `dir` with size satisfying constraints

```cpp
void FileTree::search_dir(Dir *dir, LL &output, const LL &ref);

void FileTree::search_dir(LL &output, const LL &ref) {
    search_dir(root_, output, ref);
}
```

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

A cool [visualization in reddit](https://www.reddit.com/r/adventofcode/comments/zgq3nr/2022_day_9_rope_pull/) =)

Part 1:

- The position of the head $x_{head}, y_{head}$ can be easily computed from the move commands
- If the position of the current tail is no longer "close" to the head, update it. The new position is always next to the position of the new head, on the opposite direction of the movement.
- Collect these positions into a trajectory. The movement pattern is rather simple, move diagonally one if needed, than basically just either horizontally or vertically.

Part 2: things are getting fun now

- The movement is much more complicated to just have a trajectory of few key points
- Instead, simulate the whole movement, one step at a time

-------

## Day 10

- Store the signal strengths during each cycle in an array
- Not extremely hard, just be careful when setting values

-------

## Day 11

- Reading the input was a bit tedious, but `stringstream` makes it easier
- After finishing the class `Monkey` with relevant methods, it's straight-forward.
- Simply iterate over the round, each over the monkeys and collect the result after their *"stuff-slinging simian shenanigans"*
- Part 2: As the relief no longer cases the worry level to be divided by 3, the worry level will keep increasing, and we will have to deal with very large number.
  - Notice that all the divisible checks have prime value. Thus, instead of keeping the large worry level, we could keep the modulus of it, by the product of all the prime numbers.

-------

## Day 12

Part 1:

- Simple and clean with BFS (Breadth-first search)
- For ease and speed, get the map size first, so we can use arrays
  - Number of rows from counting lines with `getline(file, line)`
  - Number of columns from `line.size()`
- Have two arrays, one for the height map, one for the distance map
- Initialize the distance map: all values to `INT_MAX` (which is enough for test case and actual input), 0 for start point
- Keep a list of position to visit, initialize this list with the starting point
- As the `to_visit` list is not empty, check the first point
  - Check all neighbor points
  - If a neighbor point is unvisited and the elevation different is with in range, set the distance to be `+1` from the current point
  - Also append the above neighbor point to the end of `to_visit` list
  - After all 4 neighbor points are checked, remove the current point from the `to_visit` list

Part 2: only one minor change

- Simply initialize the `to_visit` list with all level-`a` points

-------

## Day 13

TODO: Read [r/adventofcode](https://www.reddit.com/r/adventofcode/comments/zkmyh4/comment/j026ehh/)

-------

## Day 14

It's certainly fun to watch the output grid

![d14p1](/imgs/day14.png)

Part 1:

- Firstly, read the rock paths
- Set the range of the map according to the range of the paths
- There are two `while` loops
  - One for simulating one unit of sand falling
  - One for keeping the sand fall until stopping criteria, which, in this case, is that one sand block fall out of the required range.

Part 2: need few changes

- The range `xmin` and `xmax` is set using `ymax`
- Add the rock floor
- Add stopping criteria when the sand block is still at the falling point.

-------

## Day 15

- Strategy for part 2 is better than in part 1.
- In the end, part 2 take `~1m20s` or `20s` if search backward :)
- Part 1:
  - After reading the input, find the range of the array to check
    - `xmin` = `xmin` of all sensors - its reach
    - `xmax` = `xmax` of all sensors + its reach
  - Define a `boolean` array, which we will check at each position, whether it's covered by a sensor
- Part 2:
  - The 2D map is huge, and we do not need to keep them in memory, thus, we should not keep an 2D array around.
  - We will check one line at a time, just like in part 1, and stop when we find a possible position
  - Checking and setting values one by one is okay for part 1, but is too slow for part 2.
  - A more elegant solution is to define a new `Interval` class/struct, to represent a range of value, e.g., interval 5-9 includes values 5, 6, 7, 8, 9.
  - Create helper functions to subtract `Interval`s
  - For each row:
    - The initial interval is 0-4.000.000
    - It's easier to find the interval under the scan of a sensor.
    - We subtract that from the initial interval
    - Repeat that for all sensors and all row
  - For most rows, in the end, we end up with no interval, implying no position is possible for the distress beacon on that row.
  - Stop the loop when after subtracting all sub-intervals, we still have an interval left.

-------

## Day 18

Part 1:

- Define 3D coordinate and 3D gridmap

  ```cpp
  template<typename T>
  struct triplet
  {
      T x, y, z;
      triplet (const T &m1, const T &m2, const T &m3)
      : x(m1), y(m2), z(m3) {};
  };
  using Point = triplet<int>;

  enum BLOCK { LAVA, AIR };
  using Grid = vector<vector<vector<BLOCK>>>;
  ```

- For each `LAVA` cell, count how many of its 6 neighbors are `AIR` cells

Part 2:

- Add new type of block:

  ```cpp
  enum BLOCK { LAVA, AIR, STEAM };
  ```

- Fill the 3D gridmap with flood fill algorithm
  
  ```cpp
  void fill_steam(
      Grid &grid, const vector<int> &range, int x, int y, int z)
  {
      if (x < range[0] - 1 || x > range[1] + 1 ||
          y < range[2] - 1 || y > range[3] + 1 ||
          z < range[4] - 1 || z > range[5] + 1)
          return;
      BLOCK cell = grid[x - range[0] + 1][y - range[2] + 1][z - range[4] + 1];
      if (cell == LAVA || cell == STEAM)
          return;
      grid[x - range[0] + 1][y - range[2] + 1][z - range[4] + 1] = STEAM;
      fill_steam(grid, range, x - 1, y, z);
      fill_steam(grid, range, x + 1, y, z);
      fill_steam(grid, range, x, y - 1, z);
      fill_steam(grid, range, x, y + 1, z);
      fill_steam(grid, range, x, y, z - 1);
      fill_steam(grid, range, x, y, z + 1);
  }
  ```

- Then, just as in part 1, for each `LAVA` cell, count how many of its 6 neighbors are `STEAM` cells
