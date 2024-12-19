/*
 *   Copyright (c) 2022 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

void solve() {
    int low1, high1, low2, high2;
    char c;
    int result = 0;
    while (cin >> low1) {
        cin >> c >> high1 >> c >> low2 >> c >> high2;
#if PART1
        if ((low1 <= low2 && high1 >= high2) ||
            (low1 >= low2 && high1 <= high2))
            result++;
#else
        if ((low2 > high1) || (high2 < low1)) continue;
        result++;
#endif
    }
    cout << result << endl;
}

int main(int argc, char const *argv[]) {
    solve();
    return 0;
}
