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

string num_strs[] = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
map<string, int> m{
    {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5},
    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};


int is_num_str(const string& str, const int& id) {
    if (isdigit(str[id]))
        return str[id] - '0';
#if PART2
    for (string num_str : num_strs) {
        // Check if the remaining substring is too short
        if (num_str.size() > str.size() - id)
            continue;
        // Check if it is the same number string
        if (str.substr(id, num_str.size()) == num_str)
            return m[num_str];
    }
#endif // PART2
    return 0;
};

void solve()
{
    string line;
    int ans = 0;
    while (cin >> line) {
        // Scan for the 1st digit
        for (size_t i = 0; i < line.size(); i++) {
            int digit = is_num_str(line, i);
            if (digit) {
                ans += 10 * digit;
                break;
            }
        }

        // Scan for the 2nd digit
        for (size_t i = line.size() - 1; i >= 0; i--) {
            int digit = is_num_str(line, i);
            if (digit) {
                ans += digit;
                break;
            }
        }
    }
    cout << ans << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
