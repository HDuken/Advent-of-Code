/*
 *   Copyright (c) 2025 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

ll ans = 0;
int n_row = 0, n_col = 0;
char m[150][150];
ll cnt[150][150];
set<int> cols;

void read_input() {
    string line;
    while (getline(cin, line)) {
        copy(all(line), m[n_row]);
        n_row++;
        if (!n_col) n_col = line.size();
    }

    // Init the cnt matrix for part 2
    for (int id_row = 0; id_row < n_row; id_row++) {
        for (int id_col = 0; id_col < n_col; id_col++) {
            cnt[id_row][id_col] = 0;
        }
    }
}

void solve() {
    // Get the start position 'S'
    cols.clear();
    for (int id_col = 0; id_col < n_col; id_col++) {
        if (m[0][id_col] == 'S') {
            cols.insert(id_col);
            cnt[0][id_col] = 1;
            break;
        }
    }

    for (int id_row = 1; id_row < n_row; id_row++) {
        set<int> col_to_erase;
        for (int id_col : cols) {
            if (m[id_row][id_col] == '^') {
#if PART1
                ans++;
#endif  // PART1
                if (id_col > 0) {
                    cols.insert(id_col - 1);
                    cnt[id_row][id_col - 1] += cnt[id_row - 1][id_col];
                }
                if (id_col < n_col - 1) {
                    cols.insert(id_col + 1);
                    cnt[id_row][id_col + 1] += cnt[id_row - 1][id_col];
                }
                col_to_erase.insert(id_col);
            } else {
                cnt[id_row][id_col] += cnt[id_row - 1][id_col];
            }
        }

        for (int id_col : col_to_erase) cols.erase(id_col);
    }

#if PART2
    for (int id_col = 0; id_col < n_col; id_col++)
        ans += cnt[n_row - 1][id_col];
#endif  // PART2
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
