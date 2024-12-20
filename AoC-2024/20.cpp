/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
int n_row = 0, n_col = 0;
pii ds[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
pii s, e;
char m[141][141];
int cost[141][141];
map<int, int> cnt;
#if PART1
int n_step = 2;
#else
int n_step = 20;
#endif  // PART1

bool in_map(const pii &pt) {
    if (pt.ff < 0 || pt.ss < 0 || pt.ff >= n_row || pt.ss >= n_col)
        return false;
    return true;
}

void read_input() {
    string line;
    while (getline(cin, line)) {
        copy(all(line), m[n_row]);
        n_row++;
        if (!n_col) n_col = line.size();
    }
    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            if (m[i][j] == 'S') {
                s = pii{i, j};
            } else if (m[i][j] == 'E') {
                e = pii{i, j};
            }
            cost[i][j] = -1;
        }
    }
    cost[s.ff][s.ss] = 0;
}

void solve() {
    pii p = s;
    while (p != e) {
        for (pii d : ds) {
            pii n = p + d;
            if (!in_map(n) || m[n.ff][n.ss] == '#') continue;

            if (cost[n.ff][n.ss] == -1) {
                cost[n.ff][n.ss] = cost[p.ff][p.ss] + 1;
                p = n;
                break;
            }
        }
    }

    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            if (m[i][j] == '#') continue;
            pii p{i, j};

            int a, b;
            for (int a = -n_step; a <= n_step; a++) {
                for (int b = -(n_step - abs(a)); b <= (n_step - abs(a)); b++) {
                    pii n{i + a, j + b};
                    if (!in_map(n) || m[n.ff][n.ss] == '#') continue;
                    if (cost[n.ff][n.ss] - cost[p.ff][p.ss] <= abs(a) + abs(b))
                        continue;
                    cnt[cost[n.ff][n.ss] - cost[p.ff][p.ss] - abs(a) -
                        abs(b)]++;
                }
            }
        }
    }

    for (auto [cost_save, count] : cnt) ans += (cost_save < 100) ? 0 : count;
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
