/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
vector<pii> rules;
vector<vector<int>> updates;

void read_input() {
    string line;

    while (getline(cin, line)) {
        if (line.empty()) break;

        int a, b;
        line[2] = ' ';
        stringstream ss(line);
        ss >> a >> b;
        rules.push_back(pii(a, b));
    }

    while (getline(cin, line)) {
        replace(all(line), ',', ' ');
        stringstream ss(line);
        vector<int> v;
        int a;
        while (ss >> a) v.push_back(a);
        updates.push_back(v);
    }
}

void solve() {
    for (vector<int> update : updates) {
        bool valid = true;
        vector<pii> related_rules;

        for (pii rule : rules) {
            if (find(all(update), rule.ff) == update.end() ||
                find(all(update), rule.ss) == update.end())
                continue;
            related_rules.push_back(rule);
            if (find(all(update), rule.ff) > find(all(update), rule.ss))
                valid = false;
        }
#if PART1
        if (!valid) continue;
#else
        if (valid) continue;

        bool loop = true;
        while (loop) {
            loop = false;
            for (pii rule : related_rules) {
                if (find(all(update), rule.ff) > find(all(update), rule.ss)) {
                    iter_swap(find(all(update), rule.ff),
                              find(all(update), rule.ss));
                    loop = true;
                    continue;
                }
            }
        }
#endif  // PART1

        ans += update[update.size() / 2];
    }
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
