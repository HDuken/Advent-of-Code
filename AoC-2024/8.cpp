/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int ans = 0;
int n_row, n_col;
string line;
char m[50][50];
map<char, vector<pii>> p;

void read_input() {
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

pii operator+(const pii &p1, const pii &p2) {
    return pii{p1.ff + p2.ff, p1.ss + p2.ss};
}
pii operator-(const pii &p1, const pii &p2) {
    return pii{p1.ff - p2.ff, p1.ss - p2.ss};
}
pii operator*(const int &a, const pii &p) { return pii{a * p.ff, a * p.ss}; }
pii operator/(const pii &p, const int &a) { return pii{p.ff / a, p.ss / a}; }
pii get_node(const pii &p1, const pii &p2) { return p1 + 2 * (p2 - p1); }

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

void solve() {
#if PART1
    set<pii> nodes;
    for (const auto &[c, v] : p) {
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v.size(); j++) {
                if (i == j) continue;
                if (in_map(get_node(v[i], v[j])))
                    nodes.insert(get_node(v[i], v[j]));
                if (in_map(get_node(v[j], v[i])))
                    nodes.insert(get_node(v[j], v[i]));
            }
        }
    }

    ans = nodes.size();
#else
    set<pii> nodes;
    for (const auto &[c, v] : p) {
        if (v.size() == 1) continue;
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v.size(); j++) {
                if (i == j) continue;
                for (const auto &pt : get_nodes(v[i], v[j])) {
                    nodes.insert(pt);
                }
            }
        }
    }

    ans += nodes.size();
#endif  // PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
