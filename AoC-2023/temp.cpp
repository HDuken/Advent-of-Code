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
#define PART2 true

void solve()
{
    int ans = 0;
    string line;
    while (getline(cin, line)) {
        cout << line << endl;
    }
    cout << ans << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
