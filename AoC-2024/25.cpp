/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"
#include <algorithm>
#include <vector>

int ans = 0;
int n_row, n_col;
char m[7][5];
pii ds[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
stringstream ss;
vector<vi> v_locks;
vector<vi> v_keys;

vi get_vi() {
    vi ret;
    for (int i = 0; i < 5; i++) {
        int cnt = 0;
        for (int j = 0; j < 5; j++)
            if (m[j + 1][i] == '#') cnt++;

        ret.push_back(cnt);
    }
    return ret;
}

void read_input() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) {
            if (m[0][0] == '#') v_locks.push_back(get_vi());
            else v_keys.push_back(get_vi());

            n_row = 0;
            continue;
        }

        copy(all(line), m[n_row]);
        n_row++;
    }
    if (m[0][0] == '#') v_locks.push_back(get_vi());
    else v_keys.push_back(get_vi());
}

bool good(const vi &lock, const vi &key) {
    for (int i = 0; i < 5; i++)
        if (lock[i] + key[i] > 5) return false;

    return true;
}

void solve() {
    for (vi lock : v_locks)
        for (vi key : v_keys) ans += good(lock, key) ? 1 : 0;
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
