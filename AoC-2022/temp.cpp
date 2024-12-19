/*
 *   Copyright (c) 2022 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
int n_row = 0, n_col = 0;
pii ds[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
stringstream ss;

void read_input() {
    string line;
    while (getline(cin, line)) {
        LOG(line);
        ss.clear();
        ss.str(line);
    }
}

void solve() {
    // TODO(Duck): duck
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
