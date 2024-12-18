/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"
#include <climits>

int ans = 0;
const int N = 71;
char m[N][N];
int cost[N][N];
bool visited[N][N];

stringstream ss;
vector<pii> vs;
pii ds[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void read_input() {
    string line;
    while (getline(cin, line)) {
        replace(all(line), ',', ' ');
        ss.clear();
        ss.str(line);
        int a, b;
        ss >> b >> a;
        vs.push_back(pii{a, b});
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            m[i][j] = '.';
            cost[i][j] = INT_MAX;
            visited[i][j] = false;
        }
    }
    cost[0][0] = 0;
}

bool in_map(const pii &pt) {
    if (pt.ff < 0 || pt.ss < 0 || pt.ff >= N || pt.ss >= N) return false;
    return true;
}

void bfs() {
    vector<pii> to_visit{pii(0, 0)};

    while (!to_visit.empty()) {
        pii p = *to_visit.begin();
        if (visited[p.ff][p.ss]) {
            to_visit.erase(to_visit.begin());
            continue;
        }
        visited[p.ff][p.ss] = true;

        for (pii d : ds) {
            pii n = p + d;
            if (!in_map(n) || m[n.ff][n.ss] == '#' || visited[n.ff][n.ss])
                continue;
            cost[n.ff][n.ss] = min(cost[p.ff][p.ss] + 1, cost[n.ff][n.ss]);
            to_visit.push_back(n);
        }

        to_visit.erase(to_visit.begin());
    }
}

void solve() {
#if PART1
    for (int i = 0; i < 1024; i++) m[vs[i].ff][vs[i].ss] = '#';
    bfs();
    ans = cost[N - 1][N - 1];
#else
    ans = 2911;  // Manual binary search
    cout << "ans = " << vs[ans].ss << ',' << vs[ans].ff << endl;
#endif  // PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
