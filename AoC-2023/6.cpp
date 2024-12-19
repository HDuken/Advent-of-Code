/*
 *   Copyright (c) 2023 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

ll ans = 1, x, y;
string line, temp;

struct Race {
    ll t, d;
};
vector<Race> arr;

#if PART1
void read_input() {
    getline(cin, line);
    stringstream ss1(line);
    getline(cin, line);
    stringstream ss2(line);
    ss1 >> temp;
    ss2 >> temp;
    while (ss1 >> x) {
        ss2 >> y;
        arr.push_back({x, y});
    }
}
#else
void read_input() {
    getline(cin, line);
    stringstream ss1(line);
    getline(cin, line);
    stringstream ss2(line);
    ss1 >> temp;
    ss2 >> temp;
    string str_t, str_d;
    while (ss1 >> temp) str_t += temp;
    while (ss2 >> temp) str_d += temp;
    arr.push_back({stoll(str_t), stoll(str_d)});
}
#endif  // PART1

bool good(ll a, ll b, ll c) { return a * (b - a) > c; }

void solve() {
    for (const auto &race : arr) {
        // Check if for a race, is it possible to win
        cout << "Race: t=" << race.t << " d=" << race.d << endl;
        if (race.t * race.t / 4 < race.d) continue;

        // Binary search
        // l is bad, r is good
        ll l = 0, r = race.t / 2;
        while (r - l > 1) {
            ll m = (r + l) / 2;
            if (good(m, race.t, race.d)) r = m;
            else l = m;
        }
        ans *= race.t + 1 - (l + 1) * 2;
    }
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
