#pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#if PART1
#define PART2 false
#endif // PART1
#if PART2
#define PART1 false
#endif // PART2

#include <vector>
#include <iostream>
#include <ostream>
#include <sstream>

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

ll ans = 1, x, y;
string line, temp;

struct Race {
    ll t, d;
};
vector<Race> arr;

#if PART1
void read_input()
{
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
void read_input()
{
    getline(cin, line);
    stringstream ss1(line);
    getline(cin, line);
    stringstream ss2(line);
    ss1 >> temp;
    ss2 >> temp;
    string str_t, str_d;
    while (ss1 >> temp)
        str_t += temp;
    while (ss2 >> temp)
        str_d += temp;
    arr.push_back({stoll(str_t), stoll(str_d)});
}
#endif // PART1

bool good(ll a, ll b, ll c) {
    return a * (b - a) > c;
}

void solve()
{
    for (const auto& race : arr) {
        // Check if for a race, is it possible to win
        cout << "Race: t=" << race.t << " d=" << race.d << endl;
        if (race.t * race.t / 4 < race.d)
            continue;

        // Binary search
        // l is bad, r is good
        ll l = 0, r = race.t / 2;
        while (r - l > 1) {
            ll m = (r + l) / 2;
            if (good(m, race.t, race.d))
                r = m;
            else
                l = m;
        }
        ans *= race.t + 1 - (l + 1) * 2;
    }
    cout << ans << endl;
}

int main(int argc, char const *argv[])
{
    read_input();
    solve();
    return 0;
}
