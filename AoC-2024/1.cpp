/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

ll ans = 0;
ll a, b;
vector<ll> ids_1;
vector<ll> ids_2;

void read_input() {
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        ss >> a >> b;
        ids_1.push_back(a);
        ids_2.push_back(b);
    }
}

void solve() {
    sort(ids_1.begin(), ids_1.end());
    sort(ids_2.begin(), ids_2.end());

#if PART1
    for (int i = 0; i < ids_1.size(); i++) {
        ans += abs(ids_2[i] - ids_1[i]);
    }
#else
    auto it2 = ids_2.begin();
    for (int i = 0; i < ids_1.size(); i++) {
        while (*(it2) < ids_1[i] && it2 != ids_2.end()) {
            it2++;
        }
        int cnt = count(it2, ids_2.end(), ids_1[i]);
        ans += ids_1[i] * cnt;
    }
#endif  // PART1

    LOG(ans);
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    return 0;
}
