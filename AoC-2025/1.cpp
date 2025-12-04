/*
 *   Copyright (c) 2025 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
stringstream ss;
int dial_position = 50;

void solve() {
    string line;
    while (getline(cin, line)) {
        ss.clear();
        ss.str(line);

        char c;  // Direction of rotation
        int x;   // No. shift

        ss >> c >> x;

#ifdef PART2
        ans += x / 100;
#endif  // PART2
        x %= 100;

        if (c == 'L') dial_position -= x;
        else dial_position += x;

#ifdef PART2
        if ((dial_position > 100) ||
            (dial_position < 0 && dial_position + x > 0))
            ans += 1;
#endif  // PART2

        dial_position = (dial_position + 100) % 100;
        ans += (dial_position == 0) ? 1 : 0;
    }
}

int main(int argc, char const *argv[]) {
    solve();
    LOG(ans);
    return 0;
}
