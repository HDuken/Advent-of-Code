/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

stringstream ss;
map<string, vector<string>> m;
set<set<string>> connections;

void read_input() {
    string line, a, b;
    while (getline(cin, line)) {
        line[2] = ' ';
        ss.clear();
        ss.str(line);
        ss >> a >> b;
        if (m.count(a)) m[a].push_back(b);
        else m[a] = {b};
        if (m.count(b)) m[b].push_back(a);
        else m[b] = {a};
        connections.insert(set<string>{a, b});
    }
}

bool good(const string &s, const set<string> &set_s) {
    if (set_s.count(s)) return true;
    for (string s2 : set_s)
        if (!connections.count(set<string>{s, s2})) return false;
    return true;
}

bool is_subset(const set<string> &set_small, const set<string> &set_large) {
    for (string s : set_small)
        if (!set_large.count(s)) return false;
    return true;
}

void solve() {
    set<set<string>> groups;
    for (auto connection : connections) {
        string com1 = *connection.begin();
        string com2 = *(++connection.begin());
        for (string com3 : m[com1]) {
            if (com3 == com2) continue;
            if (find(all(m[com2]), com3) == m[com2].end()) continue;
            groups.insert(set<string>{com1, com2, com3});
        }
    }

#if PART1
    int ans = 0;
    bool good;
    for (auto group : groups) {
        good = false;
        for (string com : group)
            if (com[0] == 't') good = true;
        ans += good ? 1 : 0;
    }
#else
    set<set<string>> groups_combined;
    for (auto group : groups) {
        // If it's a subgroup, do not extend it
        bool is_subgroup = false;
        for (auto group_c : groups_combined) {
            if (is_subset(group, group_c)) {
                is_subgroup = true;
                break;
            }
        }
        if (is_subgroup) continue;

        // Try to extend it
        for (auto connection : connections) {
            string com1 = *connection.begin();
            string com2 = *(++connection.begin());
            if (good(com1, group) && good(com2, group)) {
                group.insert(com1);
                group.insert(com2);
            }
        }
        groups_combined.insert(group);
    }

    size_t max_size = 0;
    for (auto group : groups_combined) max_size = max(group.size(), max_size);
    set<string> largest_group;
    for (auto group : groups_combined) {
        if (group.size() == max_size) {
            largest_group = group;
            break;
        }
    }

    string ans;
    for (string s : largest_group) ans += s + ',';
    ans.erase(ans.end() - 1);
#endif  // PART1

    LOG(ans);
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    return 0;
}
