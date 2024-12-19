/*
 *   Copyright (c) 2023 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
stringstream ss;
vector<vector<int>> inputs;
int x;

void read_input() {
    string line;
    while (getline(cin, line)) {
        ss.clear();
        ss.str(line);
        vector<int> v;
        while (ss >> x) v.push_back(x);
        inputs.push_back(v);
    }
}

bool good(const vector<int> seq) {
    for (const int &i : seq)
        if (i != 0) return false;
    return true;
}

void solve() {
    for (vector<int> &seq : inputs) {
        int sign = 1;
        do {
#if PART1
            ans += seq.back();
#else
            ans += seq.front() * sign;
            sign *= -1;
#endif  // PART1
            vector<int> diff;
            for (int i = 1; i < seq.size(); i++)
                diff.push_back(seq[i] - seq[i - 1]);
            swap(seq, diff);
        } while (!good(seq));
    }
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
