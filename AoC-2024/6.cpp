/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int ans = 0;

vector<string> m;
int n_row, n_col;
enum DIRECTION { up = 0, right = 1, down = 2, left = 3 };
const char D[] = "^>v<";
int x = -1, y = -1;
int d;

void read_input() {
    string line;
    while (getline(cin, line)) {
        LOG(line);
        m.push_back(line);

        if (x == -1 && y == -1) {
            for (int i = 0; i < 4; i++) {
                if (line.find(D[i]) != string::npos) {
                    x = m.size() - 1;
                    y = line.find(D[i]);
                    d = i;
                    break;
                }
            }
        }
    }
    n_row = m.size();
    n_col = m[0].size();
    LOG(n_row);
    LOG(n_col);
    LOG(x);
    LOG(y);
    LOG(d);
}

void solve() {
    while (x >= 0 && y >= 0 && x < n_row && y < n_col) {
        LOG(x);
        LOG(y);
        m[x][y] = 'X';
        // The next position
        int x_new = x;
        int y_new = y;
        switch (d) {
        case 0:
            x_new--;
        case 1:
            y_new++;
        case 2:
            x_new++;
        case 3:
            y_new--;
        }

        if (m[x_new][y_new] == '#') {
            d = (d + 1) % 4;
            x_new = x;
            y_new = y;
        } else {
            x = x_new;
            y = y_new;
        }
    }

    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            ans += m[i][j] == 'X';
        }
    }
}

int main(int argc, char const *argv[]) {
#if PART2
#endif  // PART2
    read_input();
    solve();
    LOG(ans);
    return 0;
}
