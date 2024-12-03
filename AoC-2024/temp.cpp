/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;

void read_input() {
    string line;
    while (getline(cin, line)) {
        LOG(line);
        stringstream ss(line);
    }
}

void solve() {
    // TODO(Duck): duck
    LOG(ans);
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    return 0;
}
