/*
 *   Copyright (c) 2025 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

ll ans = 0;
stringstream ss;

set<pair<ll, ll>> ranges;
vector<ll> ids;

void read_input() {
    string line;
    ll a, b;
    char c;
    while (getline(cin, line)) {
        if (line.empty()) break;
        ss.clear();
        ss.str(line);
        ss >> a >> c >> b;
        ranges.insert(pair<ll, ll>(a, b));
    }

    while (getline(cin, line)) {
        ss.clear();
        ss.str(line);
        ss >> a;
        ids.push_back(a);
    }
}

bool is_good(ll id, pair<ll, ll> range) {
    if (range.ff > id || range.ss < id) return false;
    return true;
}

// Combine 2 ranges if possible
bool combined(pair<ll, ll> r1, pair<ll, ll> r2) {
    if (!is_good(r1.ff, r2) && !is_good(r1.ss, r2)) return false;

    pair<ll, ll> r_combined(min(r1.ff, r2.ff), max(r1.ss, r2.ss));
    ranges.erase(r1);
    ranges.erase(r2);
    ranges.insert(r_combined);

    return true;
}

void solve() {
#if PART1
    for (ll id : ids) {
        for (auto range : ranges) {
            if (is_good(id, range)) {
                ans++;
                break;
            }
        }
    }
#else
    bool loop, exit;
    do {
        loop = false;
        exit = false;
        for (auto r1 : ranges) {
            for (auto r2 : ranges) {
                if (r1 == r2) continue;
                if (combined(r1, r2)) {
                    loop = true;
                    exit = true;
                    break;
                }
            }
            if (exit) break;
        }
    } while (loop);

    for (auto r : ranges) ans += r.ss - r.ff + 1;
#endif  // PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
