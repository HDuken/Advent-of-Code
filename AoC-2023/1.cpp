/*
 *   Copyright (c) 2023 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;

string num_strs[] = {"one", "two",   "three", "four", "five",
                     "six", "seven", "eight", "nine"};
map<string, int> m{{"one", 1},   {"two", 2},   {"three", 3},
                   {"four", 4},  {"five", 5},  {"six", 6},
                   {"seven", 7}, {"eight", 8}, {"nine", 9}};

int is_num_str(const string &str, const int &id) {
    if (isdigit(str[id])) return str[id] - '0';
#if PART2
    for (string num_str : num_strs) {
        // Check if the remaining substring is too short
        if (num_str.size() > str.size() - id) continue;
        // Check if it is the same number string
        if (str.substr(id, num_str.size()) == num_str) return m[num_str];
    }
#endif  // PART2
    return 0;
}

void solve() {
    string line;
    while (cin >> line) {
        // Scan for the 1st digit
        for (size_t i = 0; i < line.size(); i++) {
            int digit = is_num_str(line, i);
            if (digit) {
                ans += 10 * digit;
                break;
            }
        }

        // Scan for the 2nd digit
        for (size_t i = line.size() - 1; i >= 0; i--) {
            int digit = is_num_str(line, i);
            if (digit) {
                ans += digit;
                break;
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    solve();
    LOG(ans);
    return 0;
}
