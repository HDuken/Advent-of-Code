#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>

using namespace std;
#define PART1 true

void solve()
{
    int low1, high1, low2, high2;
    char c;
    int result = 0;
    while (cin >> low1) {
        cin >> c >> high1 >> c >> low2 >> c >> high2;
#if PART1
        if ((low1 <= low2 && high1 >= high2) ||
            (low1 >= low2 && high1 <= high2))
            result++;
#else
        if ((low2 > high1) || (high2 < low1))
            continue;
        result++;
#endif
    }
    cout << result << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
