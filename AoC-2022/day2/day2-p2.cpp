#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>

using namespace std;

int get_round_score(char C1, char C2)
{
    // 0 - lost, 1 - draw, 2 - win
    int R = (C2 - 'X');
    // A(ROCK) = 1, B(PAPER) = 0, C(SCISSOR) = 2
    int P1 = (1 - (C1 - 'A') + 3) % 3;
    int P2 = (R - P1 + 3) % 3 + 1;
    return R * 3 + P2;
}

void solve()
{
    int score = 0;
    char C1, C2;
    while (cin >> C1) {
        cin >> C2;
        score += get_round_score(C1, C2);
    }
    cout << score << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
