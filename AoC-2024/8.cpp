/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
int n_row, n_col;
char m[50][50];
map<char, vector<pii>> p;

void read_input() {
    string line;
    while (getline(cin, line)) {
        copy(all(line), m[n_row]);
        n_row++;
        if (!n_col) n_col = line.size();

        for (int i = 0; i < n_col; i++) {
            if (isalpha(line[i])) p[line[i]].push_back(pii{n_row - 1, i});
            if (isdigit(line[i])) p[line[i]].push_back(pii{n_row - 1, i});
        }
    }
}

bool in_map(const pii &pt) {
    if (pt.ff < 0 || pt.ss < 0 || pt.ff >= n_row || pt.ss >= n_col)
        return false;
    return true;
}

#if PART1
vector<pii> get_nodes(const pii &p1, const pii &p2) {
    vector<pii> out;
    if (in_map(2 * p2 - p1)) out.push_back(2 * p2 - p1);
    if (in_map(2 * p1 - p2)) out.push_back(2 * p1 - p2);
    return out;
}
#else
vector<pii> get_nodes(const pii &p1, const pii &p2) {
    vector<pii> out{p1};

    pii p3 = p2 - p1;
    while (p3.ff % 2 == 0 && p3.ss % 2 == 0) p3 = p3 / 2;

    pii p = p1;
    while (in_map(p + p3)) {
        p = p + p3;
        out.push_back(p);
    }

    p = p1;
    while (in_map(p - p3)) {
        p = p - p3;
        out.push_back(p);
    }
    return out;
}
#endif  // PART1

void solve() {
    set<pii> nodes;
    for (const auto &[c, v] : p) {
        if (v.size() == 1) continue;
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v.size(); j++) {
                if (i == j) continue;
                for (const auto &pt : get_nodes(v[i], v[j])) nodes.insert(pt);
            }
        }
    }
    ans = nodes.size();
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
