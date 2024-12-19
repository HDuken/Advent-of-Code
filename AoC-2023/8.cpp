/*
 *   Copyright (c) 2023 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

ll ans = 0;
stringstream ss;
string line, instruction;
string x, y, z;
char c;
map<string, pair<string, string>> m;
vector<string> nodes;
vector<int> loops;

void read_input() {
    getline(cin, line);
    ss << line;
    ss >> instruction;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        ss.str("");
        ss.clear();
        ss << line;
        ss >> x >> c >> c >> y >> z;
        y.erase(y.begin() + 3);
        z.erase(z.begin() + 3);
        m.insert(pair<string, pair<string, string>>(x, {y, z}));
    }
}

#if PART1
void solve() {
    x = "AAA";
    int i = 0;
    while (x != "ZZZ") {
        ans++;
        if (instruction[i] == 'L') x = m[x].ff;
        else x = m[x].ss;
        i = (i + 1) % instruction.size();
    }
}
#else
void solve() {
    // Find all strings that end with 'A'
    for (const auto &[key, val] : m) {
        if (key[2] == 'A') nodes.push_back(key);
    }

    // Find the number of steps for each string to end with 'Z'
    for (string &s : nodes) {
        ans = 0;
        int i = 0;
        while (s[2] != 'Z') {
            ans++;
            if (instruction[i] == 'L') s = m[s].ff;
            else s = m[s].ss;
            i = (i + 1) % instruction.size();
        }
        loops.push_back(ans);
    }

    // Find the least common divisor
    ans = 1;
    for (const int &i : loops) ans = lcm(ans, i);
}
#endif  // PART1

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
