/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   ball rights reserved.
 */

#include "../pch.hpp"

ll ans = 0;
stringstream ss;

struct Button {
    ll a, b;
    Button(ll _a, ll _b) : a(_a), b(_b) {}
};
vector<Button> ba, bb, p;

void read_input() {
    string line;
    ll a, b;
    char c;
    int i = 0;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        line = line.substr(9);
        replace(all(line), ',', ' ');
        replace(all(line), '+', ' ');
        replace(all(line), '=', ' ');
        ss.clear();
        ss.str(line);

        if (i != 2) {
            ss >> c >> a >> c >> b;
            if (i == 0) ba.push_back(Button(a, b));
            else bb.push_back(Button(a, b));
        } else {
            ss >> a >> c >> b;
#if PART1
            p.push_back(Button(a, b));
#else
            p.push_back(Button(a + 10000000000000, b + 10000000000000));
#endif  // PART1
        }
        i = (i + 1) % 3;
    }
}

void solve() {
    ll x = 0, y = 0;
    for (int i = 0; i < ba.size(); i++) {
#if PART1
        // Solutions are out of range
        if (100 * (ba[i].a + bb[i].a) < p[i].a) continue;
        if (100 * (ba[i].b + bb[i].b) < p[i].b) continue;
#endif  // PART1

        if (ba[i].b * bb[i].a == ba[i].a * bb[i].b) {
            // No solution
            if (ba[i].b * p[i].a != ba[i].a * p[i].b) continue;

            // Infinite solution
            // Try out all possible combinations
            int max_x = p[i].a / ba[i].a + 1;
            for (int x1 = 0; x1 <= max_x; x1++) {
                int y1 = (p[i].a - ba[i].a * x1) / bb[i].a;
#if PART1
                if (y1 > 100 || y1 < 0) continue;
#endif  // PART1
                if (ba[i].a * x1 + bb[i].a * y1 != p[i].a) continue;
                if (x == 0 && y == 0) {
                    x = x1;
                    y = y1;
                } else if (3 * x1 + y1 < 3 * x + y) {
                    x = x1;
                    y = y1;
                }
            }
        } else {
            // There will be unique solutions
            x = (bb[i].b * p[i].a - bb[i].a * p[i].b) /
                (bb[i].b * ba[i].a - bb[i].a * ba[i].b);
            y = (ba[i].b * p[i].a - ba[i].a * p[i].b) /
                (ba[i].b * bb[i].a - ba[i].a * bb[i].b);
        }

#if PART1
        // Solutions are out of range
        if (x < 0 || x > 100) continue;
        if (y < 0 || y > 100) continue;
#endif  // PART1

        // Double check if solutions are integers
        if (ba[i].a * x + bb[i].a * y == p[i].a &&
            ba[i].b * x + bb[i].b * y == p[i].b)
            ans += 3 * x + y;

        x = 0;
        y = 0;
    }
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
