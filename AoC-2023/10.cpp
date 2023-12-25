#pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#if PART1
#define PART2 false
#endif // PART1
#if PART2
#define PART1 false
#endif // PART2

#include <iostream>
#include <ostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <array>
#include <numeric>
#include <algorithm>
#include <utility>

using namespace std;

const int ALPHABET = 26;
typedef long long ll;
typedef pair<int, int> pii;

#define endl        '\n'
#define all(v)      v.begin(), v.end()
#define ff          first
#define ss          second

// I/O
#define get_arr(a, n)   for(int i = 0; i < n; i++)  cin >> a[i];
#define LOG(x)          cerr << #x << " = " << x << endl;
template <typename T, typename...Ts>
constexpr void print(T&& first, Ts&&... rest) noexcept {
    if constexpr (sizeof...(Ts) == 0)   cout << first << endl;
    else {  cout << first << ' '; print(std::forward<Ts>(rest)...); }
}
template <typename T>
void print(T a[], int n) {
    for(int i = 0; i < n; i++)  cout << a[i] << " \n"[i == n - 1];
}
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vect) noexcept {
    for (const T& v : vect) { os << v << ' '; } os << endl;
    return os;
}
pii operator+(const pii& a, const pii& b) {
    return pii(a.ff + b.ff, a.ss + b.ss);
}

int ans = 0;
stringstream ss;
string line;
vector<vector<char>> grid(150, vector<char>(150, '.'));
vector<vector<int>> dist(150, vector<int>(150, 0));
pii S;
int n_row = 0, n_col = 0;
enum direction { up, down, left, right };
pii u(-1, 0), d(1, 0), l(0, -1), r(0, 1);
typedef pair<pii, direction> Point;
vector<pii> vertices;

void read_input()
{
    int j = 0;
    while (getline(cin, line)) {
        for (int i = 0; i < line.size(); i++)
             grid[n_row][i] = line[i];
        if (line.find('S') != string::npos) {
            j = line.find('S');
            S = pii{n_row, j};
        }
        n_row++;
        if (!n_col)
            n_col = line.size();
    }
}

bool good(const Point& pt) {
    const auto& [a, dir] = pt;
    if (a.ff < 0 or a.ff >= n_row)
        return false;
    if (a.ss < 0 or a.ss >= n_col)
        return false;
    char c = grid[a.ff][a.ss];
    if (c == 'S')
        return true;
    if (c == '.')
        return false;
    if (c == '|' and (dir != direction::up and dir != direction::down))
        return false;
    if (c == '-' and (dir != direction::left and dir != direction::right))
        return false;
    if (c == 'L' and (dir != direction::left and dir != direction::down))
        return false;
    if (c == 'J' and (dir != direction::right and dir != direction::down))
        return false;
    if (c == '7' and (dir != direction::up and dir != direction::right))
        return false;
    if (c == 'F' and (dir != direction::up and dir != direction::left))
        return false;
    return true;
}

Point get_next(const Point& pt) {
    const auto& [a, dir] = pt;
    char c = grid[a.ff][a.ss];
    if (c == 'S') {
        switch (dir) {
            case direction::up:         return {a + u, direction::up};
            case direction::down:       return {a + d, direction::down};
            case direction::left:       return {a + l, direction::left};
            case direction::right:      return {a + r, direction::right};
        }
    }
    if ((c == '|' and dir == direction::up) or
        (c == 'L' and dir == direction::left) or
        (c == 'J' and dir == direction::right))
        return {a + u, direction::up};
    if ((c == '|' and dir == direction::down) or
        (c == 'F' and dir == direction::left) or
        (c == '7' and dir == direction::right))
        return {a + d, direction::down};
    if ((c == '-' and dir == direction::left) or
        (c == 'J' and dir == direction::down) or
        (c == '7' and dir == direction::up))
        return {a + l, direction::left};
    if ((c == '-' and dir == direction::right) or
        (c == 'F' and dir == direction::up) or
        (c == 'L' and dir == direction::down))
        return {a + r, direction::right};
    return {a, direction::down};
}

void solve()
{
    // 4 neighboring points
    vector<pair<pii, direction>> pts;
    pts.push_back({S, direction::up});
    pts.push_back({S, direction::down});
    pts.push_back({S, direction::left});
    pts.push_back({S, direction::right});

    pair<pii, direction> pt;

    for (auto pt : pts) {
        // Re-init dist matrix and answer
        for (int i = 0; i < n_row; i++) {
            for (int j = 0; j < n_col; j++) {
                dist[i][j] = 0;
            }
        }
        ans = 0;
        vertices.clear();

        // Depth-first search
        while (good(pt)) {
            vertices.push_back(pt.ff);
            if (pt.ff == S and ans != 0) {
                print("ans", "=", (ans + 1) / 2, ans);
                return;
            }
            dist[pt.ff.ff][pt.ff.ss] = ans;
            pt = get_next(pt);
            ans++;
        }
    }
}

void solve_2() {
    int area = 0;
    for (int i = 0; i < vertices.size() - 1; i++) {
        area += vertices[i].ff * vertices[i + 1].ss;
        area -= vertices[i].ss * vertices[i + 1].ff;
    }

    area = abs(area) / 2;
    print("area =", area, "");
    ans = area + 1 - (vertices.size() - 1) / 2;
    print("ans =", ans, "");
}

int main(int argc, char const *argv[])
{
    read_input();
    solve();
#if PART2
    solve_2();
#endif // PART2
    return 0;
}
