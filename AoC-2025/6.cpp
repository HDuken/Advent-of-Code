/*
 *   Copyright (c) 2025 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

ll ans = 0;
int n_row = 0, n_col = 0;
stringstream ss;
char m[5][4000];
ll inputs[4][1000];
size_t len = 0;
char ops[1000];

void read_input() {
    string line;
    ll a;
    while (getline(cin, line)) {
        n_col = 0;
        len = max(len, line.size());
        ss.clear();
        ss.str(line);
        if (line[0] == '*') break;

        copy(all(line), m[n_row]);
        while (ss >> a) {
            inputs[n_row][n_col] = a;
            n_col++;
        }
        n_row++;
    }

    copy(all(line), m[n_row]);
    char c;
    while (ss >> c) {
        ops[n_col] = c;
        n_col++;
    }
}

void solve() {
    ll val;

#if PART1
    for (int id_col = 0; id_col < n_col; id_col++) {
        if (ops[id_col] == '+') {
            val = 0;
            for (int id_row = 0; id_row < n_row; id_row++)
                val += inputs[id_row][id_col];
        } else {
            val = 1;
            for (int id_row = 0; id_row < n_row; id_row++)
                val *= inputs[id_row][id_col];
        }
        ans += val;
    }
#else
    // Indices of the left and right char for the current math block
    int id_c_r = len - 1, id_c_l;

    for (int id_col = n_col - 1; id_col >= 0; id_col--) {
        id_c_l = id_c_r;
        while (m[n_row][id_c_l] == ' ') id_c_l--;

        // Vector to store the values reading vertically from right
        vector<ll> v;
        for (int id_c = id_c_r; id_c >= id_c_l; id_c--) {
            string s;
            for (int id_row = 0; id_row < n_row; id_row++) {
                if (m[id_row][id_c] == ' ') continue;
                s.insert(s.end(), m[id_row][id_c]);
            }
            v.push_back(stoll(s));
        }

        if (ops[id_col] == '+') {
            val = 0;
            for (ll x : v) val += x;
        } else {
            val = 1;
            for (ll x : v) val *= x;
        }
        ans += val;
        id_c_r = id_c_l - 2;
    }
#endif  // PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
