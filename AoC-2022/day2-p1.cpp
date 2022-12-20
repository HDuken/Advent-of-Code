#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>

using namespace std;

const int LOST = 0, DRAW = 3, WIN = 6;

int get_round_score(char C1, char C2)
{
    int result = 1;
    result += C2 - 'X';
    if ((C1 - 'A' + 2 - (C2 - 'X')) % 3 == 1)
        result += WIN;
    else if ((C1 - 'A' + 2 - (C2 - 'X')) % 3 == 2)
        result += DRAW;
    return result;
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
