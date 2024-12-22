/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#ifndef PCH_HPP_
#define PCH_HPP_

#pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
#include <ostream>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;  // NOLINT

const int ALPHABET = 26;
typedef long long ll;  // NOLINT
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

#define endl '\n'
#define all(v) v.begin(), v.end()
#define ff first
#define ss second

// I/O
#define get_arr(a, n)                                                          \
    for (int i = 0; i < n; i++) cin >> a[i];
#define LOG(x) cerr << #x << " = " << x << endl;
template <typename T, typename... Ts>
constexpr void print(T &&first, Ts &&...rest) noexcept {
    if constexpr (sizeof...(Ts) == 0) {
        cout << first << endl;
    } else {
        cout << first << ' ';
        print(std::forward<Ts>(rest)...);
    }
}
template <typename T> void print(T a[], int n) {
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &vect) noexcept {
    for (const T &v : vect) os << v << ' ';
    return os;
}

// Overload operators
inline pii operator+(const pii &p1, const pii &p2) {
    return pii{p1.ff + p2.ff, p1.ss + p2.ss};
}
inline pii operator-(const pii &p1, const pii &p2) {
    return pii{p1.ff - p2.ff, p1.ss - p2.ss};
}
inline pii operator*(const int &a, const pii &p) {
    return pii{a * p.ff, a * p.ss};
}
inline pii operator*(const pii &p, const int &a) {
    return pii{a * p.ff, a * p.ss};
}
inline pii operator/(const pii &p, const int &a) {
    return pii{p.ff / a, p.ss / a};
}
inline ostream &operator<<(ostream &os, const pii &p) noexcept {
    os << p.ff << ' ' << p.ss;
    return os;
}

#endif  // PCH_HPP_
