#pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#if PART1
#define PART2 false
#endif // PART1
#if PART2
#define PART1 false
#endif // PART2

#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <cmath>
#include <array>
#include <numeric>
#include <sstream>
#include <algorithm>
#include <utility>
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

int ans = 0;
vector<pair<string, int>> inputs;
const int C = 14;
#if PART1
int J = 10;
#else // PART2
const int J = 0;
#endif // PART1
map<char, int> m{{'J', J}, {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4},
                {'6', 5}, {'7', 6}, {'8', 7}, {'9', 8}, {'T', 9},
                {'Q', 11}, {'K', 12}, {'A', 13}};

int eval_hand(const string& cards) {
    int cnt[14] = {0};
    for (const char& c : cards)
        cnt[m[c]]++;
    int cnt_j = cnt[m['J']];
    // Five of a kind
    if (find(begin(cnt), end(cnt), 5) != end(cnt))
        return 6;
    // Four of a kind
    if (find(begin(cnt), end(cnt), 4) != end(cnt)) {
        #if PART2
        if (cnt_j)
            return 6;
        #endif // PART2
        return 5;
    }
    if (find(begin(cnt), end(cnt), 3) != end(cnt)) {
        // Full house
        if (find(begin(cnt), end(cnt), 2) != end(cnt)) {
            #if PART2
            if (cnt_j)
                return 6;
            #endif // PART2
            return 4;
        // Three of a kind
        } else {
            #if PART2
            if (cnt_j)
                return 5;
            #endif // PART2
            return 3;
        }
    }
    if (find(begin(cnt), end(cnt), 2) != end(cnt)) {
        int num_pair = 0;
        for (int i = 0; i < C; i++) {
            if (cnt[i] == 2)
                num_pair++;
        }
        // Two pair
        if (num_pair == 2) {
            #if PART2
            if (cnt_j == 2)
                return 5;
            else if (cnt_j == 1)
                return 4;
            #endif // PART2
            return 2;
        // One pair
        } else {
            #if PART2
            if (cnt_j)
                return 3;
            #endif // PART2
            return 1;
        }
    }
    // High card
    #if PART2
    if (cnt_j)
        return 1;
    #endif // PART2
    return 0;
}

void read_input()
{
    string line;
    int b;
    while (cin >> line >> b)
        inputs.push_back({line, b});
}

void solve()
{
    sort(all(inputs), [&](const auto& p1, const auto& p2){
        if (eval_hand(p1.ff) == eval_hand(p2.ff)) {
            for (int i = 0; i < 5; i++) {
                if (p1.ff[i] == p2.ff[i])
                    continue;
                return m[p1.ff[i]] < m[p2.ff[i]];
            }
        }
        return eval_hand(p1.ff) < eval_hand(p2.ff);
    });
    for (int i = 0; i < inputs.size(); i++)
        ans += (i + 1) * inputs[i].ss;
    cout << ans << endl;
}

int main(int argc, char const *argv[])
{
    read_input();
    solve();
    return 0;
}
