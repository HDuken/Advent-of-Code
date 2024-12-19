/*
 *   Copyright (c) 2023 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
vector<string> m;
int n_row, n_col;

void tranpose() {
    vector<string> m_tranpose(n_col, string(n_row, '.'));
    for (int i = 0; i < n_col; i++)
        for (int j = 0; j < n_row; j++) m_tranpose[i][j] = m[j][i];

    swap(m, m_tranpose);
    swap(n_row, n_col);
}

int count_diff_char(const string &s1, const string &s2) {
    int cnt = 0;
    for (int i = 0; i < s1.size() && cnt < 2; i++)
        if (s1[i] != s2[i]) cnt++;

    return cnt;
}

void solve() {
    bool ref;
    int cnt;
    int j;
    for (int i = 0; i < n_row - 1; i++) {
        ref = true;
        cnt = 0;
        j = 0;
        while (i - j >= 0 && i + 1 + j < n_row) {
#if PART1
            if (m[i - j] != m[i + 1 + j]) {
                ref = false;
                break;
            } else {
                j++;
            }
#else
            if (m[i - j] != m[i + 1 + j])
                cnt += count_diff_char(m[i - j], m[i + 1 + j]);
            j++;
#endif  // PART1
        }

#if PART1
        if (ref) {
#else
        if (cnt == 1) {
#endif  // PART1
            ans += 100 * (i + 1);
            break;
        }
    }

    tranpose();
    for (int i = 0; i < n_row - 1; i++) {
        ref = true;
        cnt = 0;
        j = 0;
        while (i - j >= 0 && i + 1 + j < n_row) {
#if PART1
            if (m[i - j] != m[i + 1 + j]) {
                ref = false;
                break;
            } else {
                j++;
            }
#else
            if (m[i - j] != m[i + 1 + j])
                cnt += count_diff_char(m[i - j], m[i + 1 + j]);
            j++;
#endif  // PART1
        }

#if PART1
        if (ref) {
#else
        if (cnt == 1) {
#endif  // PART1
            ans += (i + 1);
            break;
        }
    }
}

void read_input() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) {
            solve();
            m.clear();
            n_row = 0;
            n_col = 0;
            continue;
        }
        m.push_back(line);
        n_row++;
        if (!n_col) n_col = line.size();
    }

    solve();
}

int main(int argc, char const *argv[]) {
    read_input();
    LOG(ans);
    return 0;
}
