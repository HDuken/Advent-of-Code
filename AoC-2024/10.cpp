/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
int m[57][57];
int n_row = 0, n_col = 0;
vector<pii> ds{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool in_map(const pii &pt) {
    if (pt.ff < 0 || pt.ss < 0 || pt.ff >= n_row || pt.ss >= n_col)
        return false;
    return true;
}
pii operator+(const pii &p1, const pii &p2) {
    return pii{p1.ff + p2.ff, p1.ss + p2.ss};
}

struct Node {
    pii p;
    int v;
    Node(pii _p, int _v) : p(_p), v(_v) {}
};

struct Trail {
    pii p;
    int v;
    int cnt;
    Trail(pii _p, int _v, int _cnt) : p(_p), v(_v), cnt(_cnt) {}
};

bool operator<(const Node &n1, const Node &n2) {
    if (n1.p == n2.p) return n1.v < n2.v;
    return n1.p < n2.p;
}

vector<Node> get_neighbor_nodes(const Node &n) {
    vector<Node> nodes;
    for (auto d : ds) {
        pii v = n.p + d;
        if (in_map(v)) nodes.push_back(Node(v, m[v.ff][v.ss]));
    }
    return nodes;
}

set<Node> get_next_nodes(const set<Node> &nodes) {
    if (nodes.begin()->v == 9 || nodes.empty()) return nodes;

    set<Node> out_nodes;
    for (Node n : nodes) {
        for (Node n1 : get_neighbor_nodes(n)) {
            if (n1.v == n.v + 1) out_nodes.insert(n1);
        }
    }
    return get_next_nodes(out_nodes);
}

vector<Trail> get_next_trails(const vector<Trail> &trails) {
    if (trails.begin()->v == 9 || trails.empty()) return trails;

    vector<Trail> out_trails;
    for (Trail t : trails) {
        auto [p, v, cnt] = t;
        for (Node n1 : get_neighbor_nodes(Node(p, v))) {
            if (n1.v != v + 1) continue;
            Trail t_new(n1.p, v + 1, cnt);
            bool exist = false;
            for (auto &t_current : out_trails) {
                if (t_current.p == t_new.p) {
                    exist = true;
                    t_current.cnt += t_new.cnt;
                }
            }
            if (!exist) out_trails.push_back(t_new);
        }
    }
    return get_next_trails(out_trails);
}

void read_input() {
    string line;
    while (getline(cin, line)) {
        n_row++;
        if (!n_col) n_col = line.size();
        for (int i = 0; i < n_col; i++) {
            m[n_row - 1][i] = line[i] - '0';
        }
    }
}

void solve() {
    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            // Search for trailheads
            if (m[i][j] != 0) continue;
#if PART1
            set<Node> s{Node(pii(i, j), 0)};
            s = get_next_nodes(s);
            ans += s.size();
#else
            vector<Trail> ts{Trail(pii(i, j), 0, 1)};
            ts = get_next_trails(ts);
            for (auto t : ts) ans += t.cnt;
#endif  // PART1
        }
    }
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
