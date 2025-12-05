/*
 *   Copyright (c) 2025 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

ll ans = 0;
stringstream ss;
vector<pair<ll, ll>> ranges;

// Check if an ID is invalid
bool is_good(string s, int n_substr) {
    if (s.size() % n_substr != 0) return false;

    int len_str = s.size() / n_substr;
    for (int id_substr = 0; id_substr < n_substr; id_substr++)
        for (int id_char = 0; id_char < len_str; id_char++)
            if (s[id_char] != s[id_substr * len_str + id_char]) return false;

    return true;
}

void read_input() {
    string line;
    getline(cin, line);
    line.push_back(',');

    ss.str(line);
    ll a, b;
    char c;

    while (ss >> a >> c >> b >> c) ranges.push_back(pair<ll, ll>(a, b));
}

void solve() {
    for (const auto &[a, b] : ranges) {
        for (ll i = a; i <= b; i++) {
            string s = to_string(i);
            for (int n_substr = 2; n_substr <= s.size(); n_substr++) {
                if (is_good(s, n_substr)) {
                    ans += i;
                    break;
                }
#if PART1
                break;
#endif  // PART1
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
