#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>

#define PART1 false

using namespace std;
const int MAX = 240;    // Max no. cycles to consider
int SS[MAX + 2];        // Signal strengths during each cycle

void solve()
{
    SS[1] = 1;
    int cycle_id = 1;

    string str;
    int d;
    while (cin >> str) {
        if (str == "noop") {
            cycle_id++;
            SS[cycle_id] = SS[cycle_id - 1];
        }   else {
            cin >> d;
            cycle_id++;
            SS[cycle_id] = SS[cycle_id - 1];
            cycle_id++;
            SS[cycle_id] = SS[cycle_id - 1] + d;
        }
    }

#if PART1
    int result = 0;
    for (int i = 20; i < 221; i+=40)
        result += i * SS[i];
    cout << result <<  endl;
#else
    for (int crt = 0, line = 0; crt < 240; crt++) {
        if (crt - 40 * line == SS[crt+1] ||
            crt - 40 * line == SS[crt+1]-1 ||
            crt - 40 * line == SS[crt+1]+1)
            cout << "#";
        else
            cout << ".";
        if (crt % 40 == 39) {
            cout << endl;
            line++;
        }
    }
#endif
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
