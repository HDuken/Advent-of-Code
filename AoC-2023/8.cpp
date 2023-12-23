#include <map>
#include <string>
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
stringstream ss;
string line, instruction;
string x, y, z;
char c;
map<string, pair<string, string>> m;
vector<string> nodes;
vector<int> loops;

void read_input()
{
    getline(cin, line);
    ss << line;
    ss >> instruction;
    while (getline(cin, line)) {
        if (line.empty())
            continue;
        ss.str("");
        ss.clear();
        ss << line;
        ss >> x >> c >> c >> y >> z;
        y.erase(y.begin() + 3);
        z.erase(z.begin() + 3);
        m.insert(pair<string, pair<string, string>>(x, {y, z}));
    }
}

#if PART1
void solve()
{
    x = "AAA";
    int i = 0;
    while (x != "ZZZ") {
        ans++;
        if (instruction[i] == 'L')
            x = m[x].ff;
        else
            x = m[x].ss;
        i = (i + 1) % instruction.size();
    }
    cout << ans << endl;
}
#else
void solve()
{
    // Find all strings that end with 'A'
    for (const auto& [key, val] : m) {
        if (key[2] == 'A')
            nodes.push_back(key);
    }

    // Find the number of steps for each string to end with 'Z'
    for (string& s : nodes) {
        ans = 0;
        int i = 0;
        while (s[2] != 'Z') {
            ans++;
            if (instruction[i] == 'L')
                s = m[s].ff;
            else
                s = m[s].ss;
            i = (i + 1) % instruction.size();
        }
        loops.push_back(ans);
    }

    // Find the least common divisor
    ans = 1;
    for (const int& i : loops)
        ans = lcm(ans, i);
    cout << ans << endl;
}
#endif // PART1

int main(int argc, char const *argv[])
{
    read_input();
    solve();
    return 0;
}
