/*
 *   Copyright (c) 2025 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
stringstream ss;
char presents[6][3][3];
int present_size[6];
string line;

void read_input() {
    for (int i = 0; i < 6; i++) {
        getline(cin, line);  // Index line
        for (int j = 0; j < 3; j++) {
            getline(cin, line);
            copy(all(line), presents[i][j]);
            present_size[i] += count(all(line), '#');
        }
        getline(cin, line);  // Empty line
    }
}

void solve() {
    int a, b;
    char c;
    int area;

    while (getline(cin, line)) {
        ss.clear();
        ss.str(line);
        ss >> a >> c >> b >> c;
        area = a * b;

        int area_needed = 0;
        for (int i = 0; i < 6; i++) {
            ss >> a;
            area_needed += a * present_size[i];
        }

        if (area_needed <= area) ans++;
    }
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
