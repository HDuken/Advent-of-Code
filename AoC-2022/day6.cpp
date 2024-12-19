#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>

using namespace std;

#define PART1 true

#if PART1
const int N = 4;
#else
const int N = 14;
#endif

// True if all char is unique
bool check_unique(char str[N])
{
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (str[i] == str[j])
                return false;
        }
    }
    return true;
}

void solve()
{
    int result = N;
    char str[N];
    for (int i = 0; i < N; i++)
        cin >> str[i];

    int id = 0;
    while (!check_unique(str)) {
        cin >> str[id];
        id = (id + 1) % N;
        result++;
    }
    cout << result << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
