/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
char m[140][140];
bool visited[140][140];
int n_row = 0, n_col = 0;
vector<pii> ds{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

pii operator+(const pii &p1, const pii &p2) {
    return pii{p1.ff + p2.ff, p1.ss + p2.ss};
}

struct Edge {
    bool horizontal;
    pii p1, p2, p3, p4;
    int a, b, c, d;
    Edge(const pii &_p1, const pii &_p2) : p1(_p1), p2(_p2), p3(_p1), p4(_p2) {
        horizontal = (_p1.ss == _p2.ss) ? true : false;
        a = min(p1.ff, p2.ff);
        b = max(p1.ff, p2.ff);
        c = min(p1.ss, p2.ss);
        d = max(p1.ss, p2.ss);
    }
};

void read_input() {
    string line;
    while (getline(cin, line)) {
        copy(all(line), m[n_row]);
        n_row++;
        if (!n_col) n_col = line.size();
    }

    for (int i = 0; i < n_row; i++)
        for (int j = 0; j < n_col; j++) visited[i][j] = false;
}

bool in_map(const pii &pt) {
    if (pt.ff < 0 || pt.ss < 0 || pt.ff >= n_row || pt.ss >= n_col)
        return false;
    return true;
}

void flood_fill(const pii &p, const char &c, int &area, vector<Edge> &edges) {
    // If the point is out of the map
    if (!in_map(p)) return;
    // If already visited
    if (visited[p.ff][p.ss]) return;
    // If the point is of different class
    if (m[p.ff][p.ss] != c) return;

    visited[p.ff][p.ss] = true;
    area++;

    for (pii d : ds) {
        pii p_new = p + d;
        if (!in_map(p_new)) {
            edges.push_back(Edge(p, p_new));
            continue;
        }
        if (m[p_new.ff][p_new.ss] != c) edges.push_back(Edge(p, p_new));

        flood_fill(p_new, c, area, edges);
    }
}

void combine_edges(vector<Edge> &edges) {
    int s = edges.size();
    bool combined = false;
    for (int i = 0; i < s - 1 && !combined; i++) {
        Edge e1 = edges[i];

        for (int j = i + 1; j < s && !combined; j++) {
            Edge e2 = edges[j];

            // Skip if two edges are in different directions
            if (e1.horizontal != e2.horizontal) continue;

            if (e1.horizontal) {
                // Skip if two edges are in different line
                if (e1.a != e2.a) continue;
                // Skip if two edges are not in neighbor
                if (e1.d + 1 != e2.c && e2.d + 1 != e1.c) continue;
                if (e1.d + 1 == e2.c) {
                    if (m[e1.a][e1.d] != m[e2.a][e2.c] &&
                        m[e1.b][e1.d] != m[e2.b][e2.c])
                        continue;
                } else {
                    if (m[e2.a][e2.d] != m[e1.a][e1.c] &&
                        m[e2.b][e2.d] != m[e1.b][e1.c])
                        continue;
                }
            } else {
                // Skip if two edges are in different line
                if (e1.c != e2.c) continue;
                // Skip if two edges are not in neighbor
                if (e1.b + 1 != e2.a && e2.b + 1 != e1.a) continue;
                if (e1.b + 1 == e2.a) {
                    if (m[e1.b][e1.c] != m[e2.a][e2.c] &&
                        m[e1.b][e1.d] != m[e2.a][e2.d])
                        continue;
                } else {
                    if (m[e2.b][e2.c] != m[e1.a][e1.c] &&
                        m[e2.b][e2.d] != m[e1.a][e1.d])
                        continue;
                }
            }

            combined = true;
            Edge e = e1;
            if (e.horizontal) {
                e.c = min(e1.c, e2.c);
                e.d = max(e1.d, e2.d);
            } else {
                e.a = min(e1.a, e2.a);
                e.b = max(e1.b, e2.b);
            }
            edges.push_back(e);
            edges.erase(edges.begin() + max(i, j));
            edges.erase(edges.begin() + min(i, j));
        }
    }
    if (combined) return combine_edges(edges);
}

void solve() {
    int area;
    vector<Edge> edges;
    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            if (visited[i][j]) continue;
            area = 0;
            edges.clear();
            flood_fill(pii{i, j}, m[i][j], area, edges);
#if !PART1
            combine_edges(edges);
#endif  // !PART1
            ans += area * edges.size();
        }
    }
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
