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

int ans = 0;
stringstream ss;
string line;
vector<vector<int>> inputs;
int x;

void read_input()
{
    while (getline(cin, line)) {
        ss.str("");
        ss.clear();
        ss << line;

        vector<int> v;
        while (ss >> x)
            v.push_back(x);
        inputs.push_back(v);
    }
}

bool good(const vector<int> seq) {
    for (const int& i : seq) {
        if (i != 0)
            return false;
    }
    return true;
}

void solve()
{
    for (vector<int>& seq : inputs) {
        int sign = 1;
        do {
#if PART1
            ans += seq.back();
#else
            ans += seq.front() * sign;
            sign *= -1;
#endif // PART1
            vector<int> diff;
            for (int i = 1; i < seq.size(); i++)
                diff.push_back(seq[i] - seq[i - 1]);
            swap(seq, diff);
        } while (!good(seq));
    }
    cout << ans << endl;
}

int main(int argc, char const *argv[])
{
    read_input();
    solve();
    return 0;
}
