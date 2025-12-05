/*
 *   Copyright (c) 2025 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
const int N = 138;
char m[N][N];
int n_row = 0, n_col = 0;
vector<pii> ds{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
               {0, 1},   {1, -1}, {1, 0},  {1, 1}};

void read_input() {
    string line;
    while (getline(cin, line)) {
        n_row++;
        if (!n_col) n_col = line.size();
        copy(all(line), m[n_row - 1]);
    }
}

// Check if the roll of paper is accessible
bool is_good(int id_row, int id_col) {
    // Check if it is a roll of paper or blank space
    if (m[id_row][id_col] == '.') return false;

    int count_neighbor = 0;
    pii p_cur{id_row, id_col};
    for (pii d : ds) {
        pii p_new = p_cur + d;
        if (p_new.ff < 0 || p_new.ff >= n_row || p_new.ss < 0 ||
            p_new.ss >= n_col) {
            continue;
        }
        if (m[p_new.ff][p_new.ss] == '@') count_neighbor++;
    }

    return (count_neighbor < 4) ? true : false;
}

void solve() {
    bool loop;
    do {
        loop = false;
        for (int id_row = 0; id_row < n_row; id_row++) {
            for (int id_col = 0; id_col < n_col; id_col++) {
                if (is_good(id_row, id_col)) {
                    ans++;
#if PART2
                    m[id_row][id_col] = '.';
                    loop = true;
#endif  // PART2
                }
            }
        }
    } while (loop);
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
