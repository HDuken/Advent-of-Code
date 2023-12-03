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
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

void solve()
{
    int ans = 0;
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        int r = 0, g = 0, b = 0;
        int id, num;
        string temp, color;
        char c;

        ss >> temp >> id >> c;
        while (ss >> num >> color) {
            if (color.find("red") != string::npos)
                r = max(r, num);
            else if (color.find("green") != string::npos)
                g = max(g, num);
            else if (color.find("blue") != string::npos)
                b = max(b, num);
#if PART1
            if (r > 12 or g > 13 or b > 14)
                break;
#endif // PART1
        }

#if PART1
        if (r <= 12 and g <= 13 and b <= 14)
            ans += id;
#else // PART1
        ans += r * g * b;
#endif // PART1
    }
    cout << ans << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
