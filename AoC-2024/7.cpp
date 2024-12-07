/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

ll ans = 0;
vector<vector<ll>> vs;

void read_input() {
    string line;
    ll x;
    string s;
    while (getline(cin, line)) {
        replace(all(line), ':', ' ');
        stringstream ss(line);
        vector<ll> v;
        while (ss >> x) v.push_back(x);
        vs.push_back(v);
    }
}

ll concat(const ll &x, const ll &y) {
    string s = to_string(x);
    s += to_string(y);
    return stoll(s);
}

void solve() {
    for (vector<ll> v : vs) {
        // The set to store all possible current values
        set<ll> s{v[1]};
        for (int i = 2; i < v.size(); i++) {
            set<ll> s_new;
            for (ll val : s) {
                if (val + v[i] <= v[0]) s_new.insert(val + v[i]);
                if (val * v[i] <= v[0]) s_new.insert(val * v[i]);
#if PART2
                if (concat(val, v[i]) <= v[0]) s_new.insert(concat(val, v[i]));
#endif  // PART2
            }
            s = s_new;
        }

        if (s.find(v[0]) != s.end()) {
            ans += v[0];
        }
    }
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
