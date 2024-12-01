/*
 *   Copyright (c) 2022 Duc Huu Nguyen
 *   All rights reserved.
 */

#ifndef AOC_2024_PCH_HPP_
#define AOC_2024_PCH_HPP_

#pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#if PART1
#define PART2 false
#endif  // PART1
#if PART2
#define PART1 false
#endif  // PART2

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;  // NOLINT

const int ALPHABET = 26;
typedef long long ll;  // NOLINT
typedef pair<int, int> pii;

#define endl        '\n'
#define all(v)      v.begin(), v.end()
#define ff          first
#define ss          second

// I/O
#define get_arr(a, n)   for (int i = 0; i < n; i++)  cin >> a[i];
#define LOG(x)          cerr << #x << " = " << x << endl;
template <typename T, typename...Ts>
constexpr void print(T&& first, Ts&&... rest) noexcept {
    if constexpr (sizeof...(Ts) == 0) {
        cout << first << endl;
    } else {
        cout << first << ' ';
        print(std::forward<Ts>(rest)...); }
}
template <typename T>
void print(T a[], int n) {
    for (int i = 0; i < n; i++)  cout << a[i] << " \n"[i == n - 1];
}
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vect) noexcept {
    for (const T& v : vect) {
        os << v << ' ';
    }
    os << endl;
    return os;
}

#endif  // AOC_2024_PCH_HPP_
