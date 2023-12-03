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
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int ans = 0;
string line;

void read_input()
{
    while (getline(cin, line)) {
        cout << line;
    }
}

void solve_p1()
{
    ans = 0;
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
