/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

ll ans = 0;
vector<ll> v;
vector<pii> free_spaces;
vector<pii> file_spaces;

void read_input() {
    string line;
    cin >> line;
    for (int i = 0; i < line.size(); i++) {
        vector<ll> temp_v(line[i] - '0', (i % 2 == 0) ? i / 2 : -1);
        if (i % 2 == 0) {
            file_spaces.push_back(pii{line[i] - '0', v.size()});
        } else {
            free_spaces.push_back(pii{line[i] - '0', v.size()});
        }
        v.insert(v.end(), all(temp_v));
    }
    free_spaces.pop_back();
}

void solve() {
#if PART1
    int l = 0, r = v.size() - 1;
    while (r > l) {
        if (v[l] != -1) {
            l++;
            continue;
        }
        if (v[r] == -1) {
            r--;
            continue;
        }
        iter_swap(v.begin() + l, v.begin() + r);
        l++;
        r--;
    }
#else
    reverse(all(file_spaces));

    for (pii file : file_spaces) {
        for (int i = 0; i < free_spaces.size(); i++) {
            // If the free space is on the right of the file
            if (free_spaces[i].ss > file.ss) break;
            // If the current free space is not big enough
            if (file.ff > free_spaces[i].ff) continue;

            // Swap a file with a free space
            for (int j = 0; j < file.ff; j++) {
                iter_swap(v.begin() + file.ss + j,
                          v.begin() + free_spaces[i].ss + j);
            }

            // Update the list of free spaces
            if (file.ff == free_spaces[i].ff) {
                free_spaces.erase(free_spaces.begin() + i);
            } else {
                free_spaces[i].ff = free_spaces[i].ff - file.ff;
                free_spaces[i].ss = free_spaces[i].ss + file.ff;
            }
            break;
        }
    }
#endif  // PART1
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == -1) continue;
        ans += v[i] * i;
    }
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
