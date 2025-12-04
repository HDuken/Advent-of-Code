/*
 *   Copyright (c) 2025 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"
#include <utility>

ll ans = 0;
stringstream ss;
vector<pair<ll, ll>> ranges;

bool is_invalid(ll x) {
    string s = to_string(x);

    // If the number has odd no. digits
    if (s.size() % 2 != 0) return false;

    string s1 = s.substr(0, s.size() / 2);
    string s2 = s.substr(s.size() / 2, s.size() / 2);
    if (s1 == s2) return true;

    return false;
}

void read_input() {
    string line;
    getline(cin, line);
    line.push_back(',');

    ss.str(line);
    char c;
    ll a, b;

    while (ss >> a >> c >> b >> c) {
        ranges.push_back(pair<ll, ll>(a, b));
    }
}

void solve() {
    ll a, b;
    for (const auto &[a, b] : ranges) {
        print(a, b);
        for (ll i = a; i <= b; i++) {
            if (is_invalid(i)) ans += i;
        }
    }
}

int main(int argc, char const *argv[]) {
    read_input();
#if !PART2
    solve();
#endif  // !PART2
    LOG(ans);
    return 0;
}
