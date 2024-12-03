/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include <iostream>
#include <string>

#include "../pch.hpp"

ll ans = 0;

const char S[] = "mul(";
const char DO[] = "do()";
const char DONT[] = "don't()";

void read_input() {
    string line;
    while (getline(cin, line)) {
        size_t pos = 0;
        size_t found = line.find(S, pos);

#if !PART1
        size_t found_do = 0;
        size_t found_dont = line.find(DONT, found_do);
#endif  // !PART1

        while (found != string::npos) {
#if !PART1
            if (found > found_dont) {
                found_do = line.find(DO, found_dont);
                if (found_do == string::npos) break;

                found_dont = line.find(DONT, found_do);
                pos = found_do;
                found = line.find(S, pos);
                continue;
            }
#endif  // !PART1

            pos = found + 4;
            found = line.find(S, pos);
            string temp_string;
            ll a, b;

            if (!isdigit(line[pos])) continue;
            while (isdigit(line[pos])) {
                temp_string += line[pos];
                pos++;
            }
            if (line[pos] != ',') {
                continue;
            } else {
                a = stoll(temp_string);
                temp_string.clear();
                pos++;
            }
            if (!isdigit(line[pos])) continue;
            while (isdigit(line[pos])) {
                temp_string += line[pos];
                pos++;
            }
            if (line[pos] != ')') continue;
            else b = stoll(temp_string);

            ans += a * b;
        }
    }
}

void solve() {
    // TODO(duck)
    LOG(ans);
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    return 0;
}
// 161085926
//  83950340
