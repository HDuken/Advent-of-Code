#include <filesystem>
#pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#if PART1
#define PART2 false
#endif // PART1
#if PART2
#define PART1 false
#endif // PART2

#include <math.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>

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

struct Map {
    ll dst, src, len; 
};

vector<vector<Map>> m(7);

ll ans = 0;
string line, temp;
vector<ll> seeds;
ll a, b, c, x, y;

void read_input()
{
    getline(cin, line);
    stringstream ss(line);
    ss >> temp;
    while (ss >> x) {
        seeds.push_back(x);
    }

    int i = -1;
    while (getline(cin, line)) {
        stringstream ss(line);
        if (line.empty()) {
            i++;
            getline(cin, line);
            ss >> temp >> temp;
            continue;
        }
        ss >> a >> b >> c;
        m[i].push_back({a, b, c});
    }
}

void solve_p1()
{
    for (int i = 0; i < 7; i++) {
        for (auto& seed : seeds) {
            for (const auto& mi : m[i]) {
                if (seed >= mi.src and seed < mi.src + mi.len) {
                    seed = seed - mi.src + mi.dst;
                    break;
                }
            }
        }
    }
    ans = *min_element(all(seeds));
    cout << "P1: " << ans << endl;
}

void solve_p2()
{
    ans = 0;
    cout << "P2: " << ans << endl;
}

int main(int argc, char const *argv[])
{
    read_input();
    solve_p1();
    solve_p2();
    return 0;
}
