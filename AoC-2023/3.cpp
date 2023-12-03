#pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int ans = 0;
string line, str_num;
int num_rows = 0, num_cols = 0;
int j_start = 0, j_end = 0;

struct Num {
    int val, i, j_start, j_end;
};
struct Symbol {
    char c;
    int i, j;
};
vector<Num> nums;
vector<Symbol> symbols;

void check_num() {
    if (str_num.size()) {
        nums.push_back({stoi(str_num), num_rows, j_start, j_end});
        str_num.clear();
    }
}

void update_vects() {
    for (int j = 0; j < line.size(); j++) {
        if (isdigit(line[j])) {
            str_num += line[j];
            if (str_num.size() == 1)
                j_start = j;
            j_end = j;
        } else if (line[j] != '.') {
            symbols.push_back({line[j], num_rows, j});
            check_num();
        } else {
            check_num();
        }
    }
    check_num();
}

bool is_adjacent(const Num& n, const Symbol& s) {
    if (s.i < n.i - 1 or s.i > n.i + 1)
        return false;
    if (s.j < n.j_start - 1 or s.j > n.j_end + 1)
        return false;
    return true;
}

void read_input()
{
    while (getline(cin, line)) {
        update_vects();
        num_rows++;
    }
}

void solve_p1()
{
    ans = 0;
    for (const auto& n : nums) {
        for (const auto& s : symbols) {
            if (is_adjacent(n, s))
                ans += n.val;
        }
    }
    cout << "P1: " << ans << endl;
}

void solve_p2()
{
    ans = 0;
    for (const auto& s : symbols) {
        if (s.c == '*') {
            vector<Num> adj_nums;
            for (const auto& n : nums) {
                if (is_adjacent(n, s))
                    adj_nums.push_back(n);
            }

            if (adj_nums.size() == 2)
                ans += adj_nums[0].val * adj_nums[1].val;
        }
    }
    cout << "P2: " << ans << endl;
}

int main(int argc, char const *argv[])
{
    read_input();
    solve_p1();
    solve_p2();
    return 0;
}
