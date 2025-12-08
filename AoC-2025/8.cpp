/*
 *   Copyright (c) 2025 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

ll ans = 1;
int cnt = 0;
stringstream ss;
struct Coord {
    ll x, y, z;
    Coord() : x(0), y(0), z(0) {};
    Coord(ll _x, ll _y, ll _z) : x(_x), y(_y), z(_z) {};
};
ostream &operator<<(ostream &os, const Coord &coord) noexcept {
    os << coord.x << ' ' << coord.y << ' ' << coord.z;
    return os;
}
ll get_dist(const Coord &a, const Coord &b) {
    return pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2);
}

const int N_MAX_CONNECTION = 1000;
Coord boxes[1000];            // An array of coordinates in 3D
map<ll, vector<pii>> m_dist;  // A sorted mapping: distance-pairs of coordinates
set<ll> dists;                // A sorted set: distances between 2 coordinates

map<int, set<int>> m_circuits;  // A mapping from box ID to the circuit
set<set<int>> circuits;         // The set to store all circuits

void read_input() {
    string line;
    char c;
    while (getline(cin, line)) {
        ss.clear();
        ss.str(line);
        ll x, y, z;
        ss >> x >> c >> y >> c >> z;
        boxes[cnt] = Coord(x, y, z);
        cnt++;
    }
}

void solve() {
    // Calculate the distance between pairs of coordinates, save it in a map
    // Also, store the distances in a sorted set for later iteration
    for (int i = 0; i < cnt; i++) {
        for (int j = i + 1; j < cnt; j++) {
            ll dist = get_dist(boxes[i], boxes[j]);
            if (m_dist.find(dist) == m_dist.end())
                m_dist[dist] = vector<pii>{pii(i, j)};
            else m_dist[dist].push_back(pii(i, j));

            dists.insert(dist);
        }
    }

    int id_connection = 0;
    // Iterate over the distance, from closest to further
    for (ll dist : dists) {

#if PART1
        if (id_connection == N_MAX_CONNECTION) break;
#endif  // PART1

        for (auto [id1, id2] : m_dist[dist]) {
            set<int> c;
            if (m_circuits.find(id1) == m_circuits.end() &&
                m_circuits.find(id2) == m_circuits.end()) {
                // Both are not in any circuit, create a new circuit for them
                c.insert(id1);
                c.insert(id2);
            } else if (m_circuits.find(id1) != m_circuits.end() &&
                       m_circuits.find(id2) == m_circuits.end()) {
                // Box 1 is already in a circuit, box 2 is NOT
                // Add box 2 to box 1's current circuit
                c = m_circuits[id1];
                c.insert(id2);
                circuits.erase(m_circuits[id1]);
            } else if (m_circuits.find(id1) == m_circuits.end() &&
                       m_circuits.find(id2) != m_circuits.end()) {
                // Box 2 is already in a circuit, box 1 is NOT
                // Add box 1 to box 2's current circuit
                c = m_circuits[id2];
                c.insert(id1);
                circuits.erase(m_circuits[id2]);
            } else if (m_circuits[id1] != m_circuits[id2]) {
                // Both are already in circuits
                // Do nothing if in the same circuit
                // Combine if in the different circuits
                c = m_circuits[id1];
                c.insert(all(m_circuits[id2]));
                circuits.erase(m_circuits[id1]);
                circuits.erase(m_circuits[id2]);
            }

            circuits.insert(c);
            for (int id : c) m_circuits[id] = c;
#if PART2
            if (c.size() == cnt) {
                ans = boxes[id1].x * boxes[id2].x;
                return;
            }
#endif  // PART2
        }
        id_connection++;
    }

#if PART1
    // Store the sizes of circuits in a vector, and then sort it
    vector<int> sizes;
    for (auto c : circuits) sizes.push_back(c.size());
    std::sort(sizes.begin(), sizes.end(), std::greater<>());
    for (int i = 0; i < 3; i++) ans *= sizes[i];
#endif  // PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
