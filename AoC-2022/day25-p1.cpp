#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using SNAFU = string;
using LL = long long;
const LL P = 5;
const int S = 20;

LL EXP5[S];
void get_exp_array();

LL SNAFU2decimal(SNAFU &s);
SNAFU decimal2SNAFU(const LL &val);

void solve()
{
    LL result = 0;
    string str;
    while (cin >> str) {
        result += SNAFU2decimal(str);
    }
    cout << "Result = " << result << endl;
    cout << decimal2SNAFU(result) << endl;
}

int main(int argc, char const *argv[])
{
    get_exp_array();
    solve();
    return 0;
}

LL SNAFU2decimal(SNAFU &s)
{
    LL output = 0;
    reverse(s.begin(), s.end());
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '1')
            output += EXP5[i];
        else if (s[i] == '2')
            output += 2 * EXP5[i];
        else if (s[i] == '-')
            output -= EXP5[i];
        else if (s[i] == '=')
            output -= 2 * EXP5[i];
    }
    return output;
}

void get_exp_array()
{
    EXP5[0] = 1;
    for (int i = 1; i < S; i++) {
        EXP5[i] = EXP5[i - 1] * P;
    }
}

SNAFU decimal2SNAFU(const LL &val)
{
    if (val == 0)
        return "";
    LL r = val % 5;
    if (r == 0 || r == 1 || r == 2)
        return decimal2SNAFU(val / 5) + char(val % 5 + '0');
    else if (r == 3)
        return decimal2SNAFU(val / 5 + 1) + '=';
    else if (r == 4)
        return decimal2SNAFU(val / 5 + 1) + '-';
    return "0";
}