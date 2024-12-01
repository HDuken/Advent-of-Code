/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;  // Test

void read_input() {
    string line;
    while (getline(cin, line)) {
        cout << line << endl;
        stringstream ss(line);
    }
}

void solve() {
    // TODO
    cout << ans << endl;
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    return 0;
}
