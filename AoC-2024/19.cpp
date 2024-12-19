/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <string>
#include <vector>

int ans = 0;
int n_row = 0, n_col = 0;
pii ds[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
stringstream ss;
map<string, bool> m;
map<string, int> m_cnt;
set<string> vs;
int max_size = 0;

void read_input() {
    string line;
    getline(cin, line);
    replace(all(line), ',', ' ');
    ss.clear();
    ss.str(line);
    string s;
    while (ss >> s) {
        vs.insert(s);
        max_size = max(max_size, static_cast<int>(s.size()));
        m[s] = true;
    }
    getline(cin, line);
}

bool check(const string &s) {
    if (m.find(s) != m.end()) return m[s];
    string s1, s2;
    for (int i = 1; i < s.size(); i++) {
        s1 = s.substr(0, i);
        s2 = s.substr(i);
        if (check(s1) && check(s2)) {
            m[s] = true;
            return true;
        }
    }
    m[s] = false;
    m_cnt[s] = 0;
    return false;
}

int count(const string &s) {
    if (m_cnt.find(s) != m_cnt.end()) return m_cnt[s];
    if (s.size() == 1) {
        if (find(all(vs), s) != vs.end()) {
            m_cnt[s] = 1;
            return 1;
        } else {
            m_cnt[s] = 0;
            return 0;
        }
    }
    int cnt = 0;

    for (string str : vs) {
        if (str.size() > s.size()) continue;
        string s1 = s.substr(0, str.size());
        string s2 = s.substr(str.size());
        if (s1 == str && check(s2)) {
            cnt += count(s2);
        }
    }

    m_cnt[s] = cnt;
    return cnt;
}

void solve() {
    string line;
    while (getline(cin, line)) {
        if (check(line)) {
#if PART1
            ans++;
#else
            LOG(line);
            LOG(count(line));
            ans += count(line);
#endif  // PART1
        }
    }

#if !PART1
    // for (string s : vs) {
    //     cout << s << ' ';
    //     LOG(count(s));
    // }
#endif  // !PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
