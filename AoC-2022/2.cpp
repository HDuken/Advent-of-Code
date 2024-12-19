/*
 *   Copyright (c) 2022 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

const int LOST = 0, DRAW = 3, WIN = 6;

#if PART1
int get_round_score(char C1, char C2) {
    int result = 1;
    result += C2 - 'X';
    if ((C1 - 'A' + 2 - (C2 - 'X')) % 3 == 1) result += WIN;
    else if ((C1 - 'A' + 2 - (C2 - 'X')) % 3 == 2) result += DRAW;
    return result;
}
#else
int get_round_score(char C1, char C2) {
    // 0 - lost, 1 - draw, 2 - win
    int R = (C2 - 'X');
    // A(ROCK) = 1, B(PAPER) = 0, C(SCISSOR) = 2
    int P1 = (1 - (C1 - 'A') + 3) % 3;
    int P2 = (R - P1 + 3) % 3 + 1;
    return R * 3 + P2;
}
#endif  // PART1

void solve() {
    int score = 0;
    char C1, C2;
    while (cin >> C1) {
        cin >> C2;
        score += get_round_score(C1, C2);
    }
    cout << score << endl;
}

int main(int argc, char const *argv[]) {
    solve();
    return 0;
}
