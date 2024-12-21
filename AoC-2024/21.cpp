/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

ll ans = 0;
#if PART1
const int N_LAYERS = 4;
#else
const int N_LAYERS = 27;
#endif  // PART1
vector<string> cmds;
// The map of the positions on numeric keyboard
map<char, pii> m_nk = {
    {'7', {0, 0}}, {'8', {0, 1}}, {'9', {0, 2}}, {'4', {1, 0}},
    {'5', {1, 1}}, {'6', {1, 2}}, {'1', {2, 0}}, {'2', {2, 1}},
    {'3', {2, 2}}, {'X', {3, 0}}, {'0', {3, 1}}, {'A', {3, 2}},
};
// The map of the positions on directional keyboard
map<char, pii> m_dk = {
    {'X', {0, 0}}, {'^', {0, 1}}, {'A', {0, 2}},
    {'<', {1, 0}}, {'v', {1, 1}}, {'>', {1, 2}},
};
// The number of need steps to go from S to G by robot R
map<tuple<char, char, int>, ll> dp;

vector<string> get_path(const pii &s, const pii &e, const map<char, pii> &m) {
    if (s == m.at('X')) return {};
    if (s == e) return {"A"};

    vector<string> out;
    if (e.ff < s.ff)
        for (string s : get_path(pii(s.ff - 1, s.ss), e, m))
            out.push_back('^' + s);
    if (e.ff > s.ff)
        for (string s : get_path(pii(s.ff + 1, s.ss), e, m))
            out.push_back('v' + s);
    if (e.ss < s.ss)
        for (string s : get_path(pii(s.ff, s.ss - 1), e, m))
            out.push_back('<' + s);
    if (e.ss > s.ss)
        for (string s : get_path(pii(s.ff, s.ss + 1), e, m))
            out.push_back('>' + s);
    return out;
}

ll get_length(const char &s, const char &e, const int &level) {
    if (level == N_LAYERS - 1) return 1;
    auto key = make_tuple(s, e, level);
    if (dp.count(key)) return dp[key];

    ll cnt = -1;
    for (const string &p : (level == 0) ? get_path(m_nk[s], m_nk[e], m_nk)
                                        : get_path(m_dk[s], m_dk[e], m_dk)) {
        ll len = 0;
        char a = 'A';
        for (char b : p) {
            len += get_length(a, b, level + 1);
            a = b;
        }
        if (cnt < 0 || len < cnt) cnt = len;
    }

    dp[key] = cnt;
    return dp[key];
}

void read_input() {
    string line;
    while (getline(cin, line)) cmds.push_back(line);
}

void solve() {
    for (string cmd : cmds) {
        ll len = 0;
        char s = 'A';
        for (char e : cmd) {
            len += get_length(s, e, 0);
            s = e;
        }
        print(cmd, len);
        ans += len * stoll(cmd.substr(0, 3));
    }
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
