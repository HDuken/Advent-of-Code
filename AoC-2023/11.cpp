#include <cstddef>
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

ll ans = 0;
const ll N = 150;
#if PART1
const ll SCALE = 2;
#else
const ll SCALE = 1000000;
#endif // PART1
stringstream ss;
string line;
ll n_row = 0, n_col = 0;
vector<pair<ll, ll>> points;

void read_input()
{
    while (getline(cin, line)) {
        if (line.empty())
            break;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '#')
                points.push_back({n_row, i});
        }
        n_row++;
        if (!n_col)
            n_col = line.size();
    }
}

void solve()
{
    // Get rows, columns with galaxies
    bool visited_rows[N] = { 0 }, visited_cols[N] = { 0 };
    for (const pair<ll, ll>& pt : points) {
        visited_rows[pt.ff] = 1;
        visited_cols[pt.ss] = 1;
    }

    // Get rows, columns without galaxies
    vector<ll> missing_rows, missing_cols;
    for (size_t i = 0; i < n_row; i++) {
        if (!visited_rows[i])
            missing_rows.push_back(i);
    }
    for (size_t i = 0; i < n_col; i++) {
        if (!visited_cols[i])
            missing_cols.push_back(i);
    }

    // for (const pii& pt : points)
    //     print("Point", pt.ff, pt.ss);
    // cout << "Missing rows: " << missing_rows;
    // cout << "Missing cols: " << missing_cols;

    // Two pointers method
    // Expand rows
    {
        int i = 0, j = 0;
        while (i < points.size()) {
            while (points[i].ff > missing_rows[j] and j < missing_rows.size())
                j++;
            points[i].ff += j * (SCALE - 1);
            i++;
        }
    }

    // Two pointers method
    // Expand columns
    sort(all(points), [&](const pii& a, const pii& b) { return a.ss < b.ss; });
    {
        int i = 0, j = 0;
        while (i < points.size()) {
            while (points[i].ss > missing_cols[j] and j < missing_cols.size())
                j++;
            points[i].ss += j * (SCALE - 1);
            i++;
        }
    }
    sort(all(points));

    for (int i = 0; i < points.size() - 1; i++) {
        for (int j = i + 1; j < points.size(); j++) {
            ans += abs(points[i].ff - points[j].ff);
            ans += abs(points[i].ss - points[j].ss);
        }
    }
    // for (const pii& pt : points)
    //     print("Point", pt.ff, pt.ss);
    cout << ans << endl;
}

int main(int argc, char const *argv[])
{
    read_input();
    solve();
    return 0;
}
