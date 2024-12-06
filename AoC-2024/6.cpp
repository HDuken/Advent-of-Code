/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"
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

using point_triplet = tuple<pii, pii, pii>;

void read_input() {
    string line;
    while (getline(cin, line)) {
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
}

void solve() {
    int x_new, y_new;
#if PART1
    // Simulate the roll-out
    while (x >= 0 && y >= 0 && x < n_row && y < n_col) {
        // Mark visited positions
        m[x][y] = 'X';
        // The next position
        x_new = x;
        y_new = y;
        if (d == 0) x_new--;
        else if (d == 1) y_new++;
        else if (d == 2) x_new++;
        else if (d == 3) y_new--;

        if (x_new == -1 || x_new == n_row || y_new == -1 || y_new == n_col) {
            break;
        } else if (m[x_new][y_new] == '#') {
            d = (d + 1) % 4;
            x_new = x;
            y_new = y;
        } else {
            x = x_new;
            y = y_new;
        }
    }

    // Count visited positions
    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            ans += m[i][j] == 'X';
        }
    }
#else
    // vector of intersected points
    vector<pii> p;

    while (x >= 0 && y >= 0 && x < n_row && y < n_col) {
        // The next position
        x_new = x;
        y_new = y;
        if (d == 0) x_new--;
        else if (d == 1) y_new++;
        else if (d == 2) x_new++;
        else if (d == 3) y_new--;

        if (x_new == -1 || x_new == n_row || y_new == -1 || y_new == n_col) {
            break;
        } else if (m[x_new][y_new] == '#') {
            d = (d + 1) % 4;
            x_new = x;
            y_new = y;
            m[x][y] = '+';
            p.push_back(pii(x, y));
        } else {
            x = x_new;
            y = y_new;
            if (m[x][y] == '.') {
                m[x][y] = (d % 2 == 0 ? '|' : '-');
            } else if (m[x][y] == '|' && d % 2 == 1) {
                m[x][y] = '+';
                p.push_back(pii(x, y));
            } else if (m[x][y] == '-' && d % 2 == 0) {
                m[x][y] = '+';
                p.push_back(pii(x, y));
            }
        }
    }

    for (auto line : m) {
        LOG(line);
    }

    sort(all(p), [](pii p1, pii p2) {
        if (p1.ff == p2.ff) return p1.ss < p2.ss;
        return p1.ff < p2.ff;
    });
    // for (pii pts1 : p) {
    //     cout << pts1.ff << ' ' << pts1.ss << endl;
    // }
    // Find all triplets of intersected points
    for (pii pts1 : p) {
        for (pii pts2 : p) {
            if (pts2.ff != pts1.ff || pts2.ss <= pts1.ss) continue;
            for (pii pts3 : p) {
                if (pts3.ff == pts1.ff) continue;
                if (pts3.ss != pts1.ss && pts3.ss != pts2.ss) continue;
                // cout << "Triplet:" << endl;
                // cout << pts1.ff << ' ' << pts1.ss << endl;
                // cout << pts2.ff << ' ' << pts2.ss << endl;
                // cout << pts3.ff << ' ' << pts3.ss << endl;
            }
        }
    }

#endif  // PART1
}

int main(int argc, char const *argv[]) {
#if PART2
#endif  // PART2
    read_input();
    solve();
    LOG(ans);
    return 0;
}
