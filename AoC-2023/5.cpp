#include "../pch.hpp"

struct Map {
    ll dst, src, len;
};
struct Range {
    ll s, e, len;
};
Range C1(ll s_, ll e_) { return Range{s_, e_, e_ - s_ + 1}; }
Range C2(ll s_, ll l_) { return Range{s_, s_ + l_ - 1, l_}; }

vector<vector<Map>> m(7);
vector<Range> ranges;

bool is_combinable(const Range &r1, const Range &r2) {
    if (r1.e + 1 < r2.s or r2.e + 1 < r1.s) return false;
    return true;
}
bool is_intersect(const Range &r1, const Range &r2) {
    if (r1.e < r2.s or r2.e < r1.s) return false;
    return true;
}
Range get_intersect(const Range &r1, const Range &r2) {
    return C1(max(r1.s, r2.s), min(r1.e, r2.e));
}
Range operator+(const Range &r1, const Range &r2) {
    return C1(min(r1.s, r2.s), max(r1.e, r2.e));
}
vector<Range> operator-(const Range &r1, const Range &r2) {
    if (!is_intersect(r1, r2)) return vector<Range>{r1};
    if (r2.s <= r1.s and r2.e >= r1.e) return vector<Range>();
    if (r2.s <= r1.s and r2.e < r1.e) return vector<Range>{C1(r2.e + 1, r1.e)};
    if (r2.s > r1.s and r2.e >= r1.e) return vector<Range>{C1(r1.s, r2.s - 1)};
    return vector<Range>{C1(r1.s, r2.s - 1), C1(r2.s + 1, r1.e)};
}
ostream &operator<<(ostream &os, const Range &r) {
    os << r.s << " " << r.e << " " << r.len << endl;
    return os;
}
bool operator==(const Range &r1, const Range &r2) {
    if (r1.s == r2.s and r1.e == r2.e) return true;
    return false;
}

void clean_ranges() {
    sort(all(ranges), [](const Range &r1, const Range &r2) {
        if (r1.s == r2.s) return r1.e < r2.e;
        return r1.s < r2.s;
    });
    for (size_t i = 0; i < ranges.size(); i++) {
        for (size_t j = i + 1; j < ranges.size(); j++) {
            if (is_combinable(ranges[i], ranges[j])) {
                ranges.push_back(ranges[i] + ranges[j]);
                ranges.erase(max(i, j) + ranges.begin());
                ranges.erase(min(i, j) + ranges.begin());
                return clean_ranges();
            }
        }
    }
}

ll ans = 0;
string line, temp;
vector<ll> seeds;
ll a, b, c, x, y;

void read_input() {
    getline(cin, line);
    stringstream ss(line);
    ss >> temp;
#if PART1
    while (ss >> x) {
        seeds.push_back(x);
    }
#else   // PART1
    while (ss >> x >> y) {
        ranges.push_back(C2(x, y));
    }
#endif  // PART1

    int i = -1;
    while (getline(cin, line)) {
        if (line.empty()) {
            i++;
            getline(cin, line);
            stringstream ss(line);
            ss >> temp >> temp;
            continue;
        }
        stringstream ss(line);
        ss >> a >> b >> c;
        m[i].push_back({a, b, c});
    }
}

void solve() {
#if PART1
    for (int i = 0; i < 7; i++) {
        for (auto &seed : seeds) {
            for (const auto &mi : m[i]) {
                if (seed >= mi.src and seed < mi.src + mi.len) {
                    seed = seed - mi.src + mi.dst;
                    break;
                }
            }
        }
    }

    ans = *min_element(all(seeds));
    cout << ans << endl;
#else   // PART1
    for (int i = 0; i < 7; i++) {
        clean_ranges();
        vector<Range> ranges_new;
        while (!ranges.empty()) {
            Range r1 = ranges.back();
            bool intersect = false;
            for (const auto &mi : m[i]) {
                Range r2 = C2(mi.src, mi.len);
                if (is_intersect(r1, r2)) {
                    intersect = true;
                    ranges.pop_back();
                    Range r3 = get_intersect(r1, r2);
                    vector<Range> r4 = r1 - r2;
                    ranges_new.push_back(C2(r3.s - mi.src + mi.dst, r3.len));
                    if (!r4.empty()) {
                        for (auto &r : r4) ranges.push_back(r);
                    }
                    break;
                }
            }
            if (intersect) continue;
            ranges_new.push_back(ranges.back());
            ranges.pop_back();
        }
        swap(ranges, ranges_new);
    }

    ans = ranges[0].s;
    for (const auto &r : ranges) ans = min(ans, r.s);
    cout << ans << endl;
#endif  // PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    return 0;
}
