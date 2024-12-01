/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#if PART1
#define PART2 false
#endif // PART1
#if PART2
#define PART1 false
#endif // PART2

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

const int ALPHABET = 26;
typedef long long ll;
typedef pair<int, int> pii;

#define endl '\n'
#define all(v) v.begin(), v.end()
#define ff first
#define ss second

// I/O
#define get_arr(a, n)                                                          \
  for (int i = 0; i < n; i++)                                                  \
    cin >> a[i];
#define LOG(x) cerr << #x << " = " << x << endl;
template <typename T, typename... Ts>
constexpr void print(T &&first, Ts &&...rest) noexcept {
  if constexpr (sizeof...(Ts) == 0)
    cout << first << endl;
  else {
    cout << first << ' ';
    print(std::forward<Ts>(rest)...);
  }
}
template <typename T> void print(T a[], int n) {
  for (int i = 0; i < n; i++)
    cout << a[i] << " \n"[i == n - 1];
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &vect) noexcept {
  for (const T &v : vect) {
    os << v << ' ';
  }
  os << endl;
  return os;
}

int ans = 0;
stringstream ss;
string line;

void read_input() {
  while (getline(cin, line)) {
    cout << line << endl;
  }
}

void solve() { cout << ans << endl; }

int main(int argc, char const *argv[]) {
  read_input();
  solve();
  return 0;
}
