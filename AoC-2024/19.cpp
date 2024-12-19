/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

ll ans = 0;
stringstream ss;
map<string, bool> m;
map<string, ll> m_cnt;
map<string, vector<pair<string, string>>> m_special;
vector<string> vs;

void read_input() {
    string line;
    getline(cin, line);
    replace(all(line), ',', ' ');
    ss.clear();
    ss.str(line);
    string s;
    while (ss >> s) {
        vs.push_back(s);
        m[s] = true;
    }
    getline(cin, line);

    sort(all(vs), [](const string &s1, const string &s2) {
        if (s1.size() == s2.size()) return s1 < s2;
        return s1.size() < s2.size();
    });
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

ll count(const string &str) {
    if (m_cnt.find(str) != m_cnt.end()) return m_cnt[str];

    ll cnt = 0;
    for (string s : vs) {
        if (str[0] != s[0] || s.size() > str.size()) continue;
        if (str.size() == s.size()) {
            if (str == s) cnt++;
            continue;
        }

        // str.size() > s.size()
        string s1 = str.substr(0, s.size());
        string s2 = str.substr(s.size());
        if (s != s1 || !check(s2)) continue;

        cnt += count(s1) * count(s2);
        if (m_special.find(s) != m_special.end())
            for (auto [sa, sb] : m_special[s]) cnt -= count(sb) * count(s2);
    }

    m_cnt[str] = cnt;
    return cnt;
}

void solve() {
#if !PART1
    for (string s : vs) {
        count(s);
        if (m_cnt[s] == 1) continue;
        for (string s1 : vs) {
            if (s1.size() >= s.size()) continue;
            string s2 = s.substr(0, s1.size());
            string s3 = s.substr(s1.size());
            if (s1 != s2 || !m[s3]) continue;
            if (m_special.find(s) != m_special.end())
                m_special[s].push_back(make_pair(s2, s3));
            else m_special[s] = vector<pair<string, string>>{make_pair(s2, s3)};
        }
    }
#endif  // !PART1

    string line;
    while (getline(cin, line)) {
        if (check(line)) {
#if PART1
            ans++;
#else
            ans += count(line);
#endif  // PART1
        }
    }
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
