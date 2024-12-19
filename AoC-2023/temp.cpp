/*
 *   Copyright (c) 2023 Duc Huu Nguyen
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
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
