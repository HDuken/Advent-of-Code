/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

ll ans = 0;
vector<ll> v;
map<ll, map<int, ll>> m;

void read_input() {
    ll i;
    while (cin >> i) v.push_back(i);
}

vector<ll> get_values(const ll &val) {
    vector<ll> out;
    string str = to_string(val);
    if (val == 0) {
        out.push_back(1);
    } else if (str.size() % 2 == 0) {
        out.push_back(stoll(str.substr(0, str.size() / 2)));
        out.push_back(stoll(str.substr(str.size() / 2)));
    } else {
        out.push_back(val * 2024);
    }
    return out;
}

ll get_score(const ll &val, const int &cnt) {
    if (m[val][cnt]) return m[val][cnt];
    if (cnt == 0) return 1;

    ll score = 0;
    for (ll sub_val : get_values(val)) {
        score += get_score(sub_val, cnt - 1);
    }
    m[val][cnt] = score;
    return score;
}

void solve() {
#if PART1
    for (int i = 0; i < v.size(); i++) ans += get_score(v[i], 25);
#else
    for (int i = 0; i < v.size(); i++) ans += get_score(v[i], 75);
#endif  // PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
