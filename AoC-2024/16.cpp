/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"
#include <algorithm>
#include <climits>
#include <utility>
#include <vector>

int ans = 0;
char m[141][141];
int v[141][141][4];
int n_row = 0, n_col = 0;
stringstream ss;
pii s, e;
vector<pii> ds{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void read_input() {
    string line;
    while (getline(cin, line)) {
        copy(all(line), m[n_row]);
        n_row++;
        if (!n_col) n_col = line.size();
    }

    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            if (m[i][j] == 'S') s = pii(i, j);
            if (m[i][j] == 'E') e = pii(i, j);

            for (int k = 0; k < 4; k++) {
                v[i][j][k] = -1;
            }
        }
    }
}

void solve() {
    v[s.ff][s.ss][0] = 0;
    set<pii> to_visit{s};
    while (!to_visit.empty()) {
        set<pii> temp_to_visit;
        for (pii p : to_visit) {
            for (int i = 0; i < 4; i++) {
                if (v[p.ff][p.ss][i] != -1) {
                    // In place rotation
                    if (v[p.ff][p.ss][(i + 1) % 4] == -1 ||
                        v[p.ff][p.ss][(i + 1) % 4] > v[p.ff][p.ss][i] + 1000) {
                        v[p.ff][p.ss][(i + 1) % 4] = v[p.ff][p.ss][i] + 1000;
                        temp_to_visit.insert(p);
                    }
                    if (v[p.ff][p.ss][(i + 3) % 4] == -1 ||
                        v[p.ff][p.ss][(i + 3) % 4] > v[p.ff][p.ss][i] + 1000) {
                        v[p.ff][p.ss][(i + 3) % 4] = v[p.ff][p.ss][i] + 1000;
                        temp_to_visit.insert(p);
                    }

                    pii n = p + ds[i];
                    if (m[n.ff][n.ss] == '#') continue;
                    if (v[n.ff][n.ss][i] == -1 ||
                        v[n.ff][n.ss][i] > v[p.ff][p.ss][i] + 1) {
                        v[n.ff][n.ss][i] = v[p.ff][p.ss][i] + 1;
                        temp_to_visit.insert(n);
                    }
                }
            }
        }
        swap(to_visit, temp_to_visit);
    }

#if PART1
    ans = INT_MAX;
    for (int i = 0; i < 4; i++) ans = min(ans, v[e.ff][e.ss][i]);
#else
    int id_min = 0;
    for (int i = 1; i < 4; i++)
        if (v[e.ff][e.ss][i] < v[e.ff][e.ss][id_min]) id_min = i;

    set<pair<pii, int>> to_visit_2{make_pair(e, id_min)};
    to_visit.insert(e);
    while (!to_visit_2.empty()) {
        set<pair<pii, int>> temp_to_visit;
        for (auto [p, id] : to_visit_2) {
            if (m[p.ff][p.ss] == '.') m[p.ff][p.ss] = 'O';
            if (v[p.ff][p.ss][(id + 1) % 4] + 1000 == v[p.ff][p.ss][id])
                temp_to_visit.insert(make_pair(p, (id + 1) % 4));
            if (v[p.ff][p.ss][(id + 3) % 4] + 1000 == v[p.ff][p.ss][id])
                temp_to_visit.insert(make_pair(p, (id + 3) % 4));
            pii prev = p - ds[id];
            if (m[prev.ff][prev.ss] != '#' &&
                v[prev.ff][prev.ss][id] + 1 == v[p.ff][p.ss][id])
                temp_to_visit.insert(make_pair(prev, id));
        }
        swap(to_visit_2, temp_to_visit);
    }

    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++)
            if (m[i][j] != '#' && m[i][j] != '.') ans++;
    }
#endif  // PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
