/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
const char XMAS[] = "XMAS";
vector<string> puzzle;
int n_row, n_col;

void read_input() {
    string line;
    while (getline(cin, line)) {
        puzzle.push_back(line);
    }
    n_row = puzzle.size();
    n_col = puzzle[0].size();
}

void solve() {
    string s;

#if PART1
    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            if (puzzle[i][j] != 'X') continue;

            // horizontal, left to right
            if (j < n_col - 3) {
                s += puzzle[i][j];
                s += puzzle[i][j + 1];
                s += puzzle[i][j + 2];
                s += puzzle[i][j + 3];
                ans += (s == XMAS);
                s.clear();
            }
            // horizontal, right to left
            if (j > 2) {
                s += puzzle[i][j];
                s += puzzle[i][j - 1];
                s += puzzle[i][j - 2];
                s += puzzle[i][j - 3];
                ans += (s == XMAS);
                s.clear();
            }
            // vertical, up to down
            if (i < n_row - 3) {
                s += puzzle[i][j];
                s += puzzle[i + 1][j];
                s += puzzle[i + 2][j];
                s += puzzle[i + 3][j];
                ans += (s == XMAS);
                s.clear();
            }
            // vertical, down to up
            if (i > 2) {
                s += puzzle[i][j];
                s += puzzle[i - 1][j];
                s += puzzle[i - 2][j];
                s += puzzle[i - 3][j];
                ans += (s == XMAS);
                s.clear();
            }
            // diagonal, top left to bottom right
            if (i < n_row - 3 && j < n_col - 3) {
                s += puzzle[i][j];
                s += puzzle[i + 1][j + 1];
                s += puzzle[i + 2][j + 2];
                s += puzzle[i + 3][j + 3];
                ans += (s == XMAS);
                s.clear();
            }
            // diagonal, bottom right to top left
            if (i > 2 && j > 2) {
                s += puzzle[i][j];
                s += puzzle[i - 1][j - 1];
                s += puzzle[i - 2][j - 2];
                s += puzzle[i - 3][j - 3];
                ans += (s == XMAS);
                s.clear();
            }
            // diagonal, bottom left to top right
            if (i < n_row - 3 && j > 2) {
                s += puzzle[i][j];
                s += puzzle[i + 1][j - 1];
                s += puzzle[i + 2][j - 2];
                s += puzzle[i + 3][j - 3];
                ans += (s == XMAS);
                s.clear();
            }
            // diagonal, top right to bottom left
            if (i > 2 && j < n_col - 3) {
                s += puzzle[i][j];
                s += puzzle[i - 1][j + 1];
                s += puzzle[i - 2][j + 2];
                s += puzzle[i - 3][j + 3];
                ans += (s == XMAS);
                s.clear();
            }
        }
    }
#else
    for (int i = 1; i < n_row - 1; i++) {
        for (int j = 1; j < n_col - 1; j++) {
            if (puzzle[i][j] != 'A') continue;
            // Check that the opposite letters are different
            if (puzzle[i - 1][j - 1] == puzzle[i + 1][j + 1]) continue;
            if (puzzle[i - 1][j + 1] == puzzle[i + 1][j - 1]) continue;
            s += puzzle[i - 1][j - 1];
            s += puzzle[i + 1][j - 1];
            s += puzzle[i - 1][j + 1];
            s += puzzle[i + 1][j + 1];
            if (count(all(s), 'M') == 2 && count(all(s), 'S') == 2) ans++;
            s.clear();
        }
    }
#endif  // PART1

    LOG(ans);
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    return 0;
}
