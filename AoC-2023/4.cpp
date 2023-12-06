#pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

int ans = 0;
string line;
string card, num;
int id;
char c;
vector<vector<int>> vects_winning_nums, vects_nums;

void read_input()
{
    while (getline(cin, line)) {
        stringstream ss(line);
        ss >> card >> id >> c;
        vector<int> vect_winning_nums, vect_nums;
        while (ss >> num and num != "|")
            vect_winning_nums.push_back(stoi(num));
        while (ss >> num)
            vect_nums.push_back(stoi(num));
        vects_winning_nums.push_back(vect_winning_nums);
        vects_nums.push_back(vect_nums);
    }
}

void solve_p1()
{
    ans = 0;
    for (int i = 0; i < vects_winning_nums.size(); i++) {
        int pt = 0;
        for (const int& n : vects_nums[i]) {
            if (find(vects_winning_nums[i].begin(),
                     vects_winning_nums[i].end(), n) != vects_winning_nums[i].end()) {
                pt = max(pt + 1, pt * 2);
            }
        }
        ans += pt;
    }
    cout << "P1: " << ans << endl;
}

void solve_p2()
{
    ans = 0;
    vector<int> cnt_match(vects_winning_nums.size(), 0);
    vector<int> cnt_card(vects_winning_nums.size(), 1);
    for (int i = 0; i < vects_winning_nums.size(); i++) {
        int num_match = 0;
        for (const int& n : vects_nums[i]) {
            if (find(vects_winning_nums[i].begin(),
                     vects_winning_nums[i].end(), n) != vects_winning_nums[i].end()) {
                num_match++;
            }
        }
        cnt_match[i] = num_match;
    }
    for (int i = 0; i < cnt_match.size(); i++) {
        if (!cnt_match[i])
            continue;
        for (int j = 1; j <= cnt_match[i] and i + j <= cnt_match.size(); j++) {
            cnt_card[i + j] += cnt_card[i];
        }
    }
    ans = accumulate(cnt_card.begin(), cnt_card.end(), 0);
    cout << "P2: " << ans << endl;
}

int main(int argc, char const *argv[])
{
    read_input();
    solve_p1();
    solve_p2();
    return 0;
}
