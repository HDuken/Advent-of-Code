/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"
#include <algorithm>
#include <clocale>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>

ll ans = 0;
ll v[1600];
int cnt;
map<int, int> dp;
map<tuple<int, int, int, int>, int> dp_cost;

const int MOD = 16777216;

void read_input() {
    string line;
    while (getline(cin, line)) {
        v[cnt] = stoll(line);
        cnt++;
    }
}

ll get_val(const ll &val) {
    if (dp.count(val)) return dp[val];
    ll x = val;
    x = ((x << 6) ^ x) % MOD;
    x = ((x >> 5) ^ x) % MOD;
    x = ((x << 11) ^ x) % MOD;
    return dp[val] = x;
}

void solve() {
    // TODO(Duck): duck
#if PART1
    for (int i = 0; i < cnt; i++) {
        ll val = v[i];
        for (int j = 0; j < 2000; j++) {
            val = get_val(val);
        }
        ans += val;
    }
#else
    for (int i = 0; i < cnt; i++) {
        set<tuple<int, int, int, int>> s;
        ll val = v[i];
        int arr[2000 + 1];
        int changes[2000 + 1];
        arr[0] = val % 10;

        for (int j = 0; j < 2000 + 1; j++) {
            val = get_val(val);
            arr[j + 1] = val % 10;
        }
        for (int j = 2000; j > 0; j--) changes[j] = arr[j] - arr[j - 1];
        for (int j = 4; j < 2000 + 1; j++) {
            auto key = make_tuple(changes[j - 3], changes[j - 2],
                                  changes[j - 1], changes[j]);
            if (s.count(key)) continue;
            dp_cost[key] += arr[j];
            s.insert(key);
        }
    }

    // for (auto [key, val] : dp_cost) {
    //     cout << get<0>(key) << ", " << get<1>(key) << ", " << get<2>(key)
    //          << ", " << get<3>(key) << ": " << val << endl;
    // }
    //
    // LOG(dp_cost[make_tuple(-2, 1, -1, 3)]);
    ans = 0;
    for (auto [key, val] : dp_cost) ans = max(ans, (ll)val);

#endif  // PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
