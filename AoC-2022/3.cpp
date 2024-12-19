#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <string>
#include <array>

using namespace std;
#define PART1 false

int char2int(const char c)
{
    if (isupper(c))
        return c - 'A' + 27;
    return c - 'a' + 1;
}

void solve()
{
    array<int, 53> chars;
    int result = 0;

#if PART1
    string str;
    while (cin >> str) {
        int N = str.size() / 2;
        string_view bag1(str.c_str(), N);
        string_view bag2(str.c_str() + N, N);
#else
    string bag1, bag2, bag3;
    while (cin >> bag1) {
        cin >> bag2 >> bag3;
#endif
        chars.fill(0);
        for (char c : bag1)
            chars[char2int(c)] = 1;
        for (char c : bag2) {
            if (chars[char2int(c)] == 1)
                chars[char2int(c)] = 2;
        }
#if !PART1
        for (char c : bag3) {
            if (chars[char2int(c)] == 2)
                chars[char2int(c)] = 3;
        }
#endif

        for (int i = 0; i < 53; i++) {
#if PART1
            if (chars[i] == 2)
#else
            if (chars[i] == 3)
#endif
                result += i;
        }
    }
    cout << result << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
