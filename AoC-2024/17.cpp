/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

vector<ll> ans;
stringstream ss;
ll r[3];
vector<ll> v;
int pt = 0;

void read_input() {
    string line;

    for (int i = 0; i < 3; i++) {
        getline(cin, line);
        line = line.substr(12);
        ss.clear();
        ss.str(line);
        ss >> r[i];
    }

    getline(cin, line);
    getline(cin, line);
    line = line.substr(9);
    replace(all(line), ',', ' ');
    ss.clear();
    ss.str(line);
    ll x;
    while (ss >> x) v.push_back(x);
}

ll literal_op(const ll &op) { return op; }
ll combo_op(const ll &op) {
    if (op < 4) return op;
    for (int i = 0; i < 3; i++)
        if (op == (4 + i)) return r[i];
    return 0;
}

// Division on register A, store in A
void adv() {
    r[0] = r[0] / pow(2, combo_op(v[pt + 1]));
    pt += 2;
}
// XOR on register B, store in B
void bxl() {
    r[1] = r[1] ^ literal_op(v[pt + 1]);
    pt += 2;
}
// Modulo, store in B
void bst() {
    r[1] = combo_op(v[pt + 1]) % 8;
    pt += 2;
}
// Jump
void jnz() {
    if (r[0] == 0) {
        pt += 2;
        return;
    }
    pt = v[pt + 1];
}
// XOR on register B and C, store in B
void bxc() {
    r[1] = r[1] ^ r[2];
    pt += 2;
}
// XOR on register B and C, store in B
void out() {
    int res = combo_op(v[pt + 1]) % 8;
    pt += 2;
    ans.push_back(res);
}
// Division on register A, store in B
void bdv() {
    r[1] = r[0] / pow(2, combo_op(v[pt + 1]));
    pt += 2;
}
// Division on register A, store in C
void cdv() {
    r[2] = r[0] / pow(2, combo_op(v[pt + 1]));
    pt += 2;
}

void solve() {
#if PART1
    while (pt < v.size()) {
        if (v[pt] == 0) adv();
        else if (v[pt] == 1) bxl();
        else if (v[pt] == 2) bst();
        else if (v[pt] == 3) jnz();
        else if (v[pt] == 4) bxc();
        else if (v[pt] == 5) out();
        else if (v[pt] == 6) bdv();
        else if (v[pt] == 7) cdv();
    }
#else
    vector<set<ll>> va;
    for (int i = 0; i < 17; i++) {
        set<ll> s;
        va.push_back(s);
    }
    va[16].insert(0);

    for (int i = 16; i >= 0; i--) {
        for (ll a : va[i]) {
            for (ll d = 0; d < 8; d++) {
                ll a_prev = 8 * a + d;
                ll c = a_prev / pow(2, (a_prev % 8) ^ 1);
                ll b = (((a_prev % 8) ^ 1) ^ 5) ^ c;
                if (b % 8 == v[i - 1]) va[i - 1].insert(a_prev);
            }
        }
    }
    ans.insert(ans.begin(), all(va[0]));
#endif  // PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
#if PART1
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << ((i < ans.size() - 1) ? ',' : endl);
#else
    LOG(ans[0]);
#endif  // PART1
    return 0;
}
