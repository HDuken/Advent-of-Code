/*
 *   Copyright (c) 2025 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

ll ans = 0;

// Get the largest joltage given the string and the number of digits
ll get_val(string line, int n_digits) {
    string s;

    // Index of the digit in the input line
    int id_pre = -1;
    int id_cur;

    for (int id_d = 0; id_d < n_digits; id_d++) {
        id_cur = id_pre + 1;
        for (size_t i = id_pre + 1; i < line.size() - n_digits + 1 + id_d;
             i++) {
            if (line[id_cur] < line[i]) id_cur = i;
        }

        s.push_back(line[id_cur]);
        id_pre = id_cur;
    }

    return stoll(s);
}

void solve() {
    string line;
#if PART1
    int n_digits = 2;
#else
    int n_digits = 12;
#endif  // PART1

    while (getline(cin, line)) ans += get_val(line, n_digits);
}

int main(int argc, char const *argv[]) {
    solve();
    LOG(ans);
    return 0;
}
