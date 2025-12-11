/*
 *   Copyright (c) 2025 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"
const int MAX_RANGE = 99'000;
// const int MAX_RANGE = 15;

ll ans = 0;
stringstream ss;
vector<pii> inputs;
pii D = pii(1, 1);
map<ll, pii> m_area;  // A sorted map: key-area, value-indices of 2 vertices
map<pii, int> m_cnt;  // A sorted map: key-vertex, val-cnt intersections

void read_input() {
    string line;
    int a, b;
    char c;

    while (getline(cin, line)) {
        ss.clear();
        ss.str(line);
        ss >> a >> c >> b;
        inputs.push_back(pii(a, b));
    }

    // Wrap: place the first point to last
    inputs.push_back(inputs[0]);
}

bool is_edge_point(const pii &p) {
    // Iterate over pair of continuous vertices
    for (int i = 0; i < inputs.size() - 1; i++) {
        pii p1 = min(inputs[i], inputs[i + 1]);
        pii p2 = max(inputs[i], inputs[i + 1]);
        if (p1.ff <= p.ff && p.ff <= p2.ff && p1.ss <= p.ss && p.ss <= p2.ss)
            return true;
    }
    return false;
}

int get_n_intersect(const pii &p) {
    if (m_cnt.find(p) != m_cnt.end()) return m_cnt[p];
    if (p.ff == MAX_RANGE || p.ss == MAX_RANGE) {
        m_cnt[p] = 0;
    } else {
        if (find(all(inputs), p) != inputs.end()) {
            m_cnt[p] = get_n_intersect(p + D) + 1;
        } else if (is_edge_point(p)) {
            m_cnt[p] = get_n_intersect(p + D) + 1;
        } else {
            m_cnt[p] = get_n_intersect(p + D);
        }
    }
    return m_cnt[p];
}

// Ray Casting Algorithm (Even–Odd Rule)
// Draw an imaginary diagonal ray to the bottom right from the test point.
// Count how many times the ray intersects polygon edges:
// Odd count → point is INSIDE
// Even count → point is OUTSIDE
bool is_good_point(const pii &p) {
    if (is_edge_point(p)) return true;

    int n_intersect = get_n_intersect(p);
    return n_intersect % 2;
}

bool is_good_rectangle(const pii &p1, const pii &p2) {
    int x_min = min(p1.ff, p2.ff);
    int x_max = max(p1.ff, p2.ff);
    int y_min = min(p1.ss, p2.ss);
    int y_max = max(p1.ss, p2.ss);

    for (int x = x_min; x <= x_max; x++) {
        if (!is_good_point(pii(x, y_min))) return false;
        if (!is_good_point(pii(x, y_max))) return false;
    }
    for (int y = y_min; y <= y_max; y++) {
        if (!is_good_point(pii(x_min, y))) return false;
        if (!is_good_point(pii(x_max, y))) return false;
    }
    return true;
}

ll get_area(const pii &a, const pii &b) {
    return (ll)(abs(a.ff - b.ff) + 1) * (ll)(abs(a.ss - b.ss) + 1);
}

void solve() {
    for (int i = 0; i < inputs.size() - 2; i++) {
        for (int j = i + 1; j < inputs.size() - 1; j++) {
            ll area = get_area(inputs[i], inputs[j]);
#if PART1
            ans = max(ans, area);
#else
            m_area[area] = pii(i, j);
#endif  // PART1
        }
    }

#if !PART1
    for (auto iter = m_area.rbegin(); iter != m_area.rend(); iter++) {
        ll area = iter->first;
        auto [i, j] = iter->second;
        print(area, i, j);
        if (is_good_rectangle(inputs[i], inputs[j])) {
            ans = area;
            break;
        }
    }

#endif  // !PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
