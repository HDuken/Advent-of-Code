/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

ll ans = 0;
pii ds[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
stringstream ss;
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
pii s_nk{m_nk['A']};
pii s_dk{m_dk['A']};

set<string> get_cmd_num(const set<string> &cmds_in) {
    set<string> cmds_out{""};
    pii p = s_nk, mid_point;
    for (string cmd_in : cmds_in) {
        for (char button : cmd_in) {
            set<string> cmds_temp;
            int x = (m_nk[button] - p).ff;
            int y = (m_nk[button] - p).ss;
            mid_point = pii{m_nk[button].ff, p.ss};
            if (mid_point != m_nk['X']) {
                for (string cmd : cmds_out) {
                    if (x > 0) cmd.append(x, 'v');
                    else if (x < 0) cmd.append(-x, '^');
                    if (y > 0) cmd.append(y, '>');
                    else if (y < 0) cmd.append(-y, '<');
                    cmd.append(1, 'A');
                    cmds_temp.insert(cmd);
                }
            }
            mid_point = pii{p.ff, m_nk[button].ss};
            if (mid_point != m_nk['X']) {
                for (string cmd : cmds_out) {
                    if (y > 0) cmd.append(y, '>');
                    else if (y < 0) cmd.append(-y, '<');
                    if (x > 0) cmd.append(x, 'v');
                    else if (x < 0) cmd.append(-x, '^');
                    cmd.append(1, 'A');
                    cmds_temp.insert(cmd);
                }
            }
            swap(cmds_out, cmds_temp);
            p = m_nk[button];
        }
    }
    return cmds_out;
}

set<string> get_cmd_dir(const set<string> &cmds_in) {
    set<string> cmds_out;
    for (string cmd_in : cmds_in) {
        set<string> cmds_out_individual{""};
        pii p = s_dk, mid_point;
        for (char button : cmd_in) {
            set<string> cmds_temp;
            int x = (m_dk[button] - p).ff;
            int y = (m_dk[button] - p).ss;
            mid_point = pii{m_nk[button].ff, p.ss};
            if (mid_point != m_nk['X']) {
                for (string cmd : cmds_out_individual) {
                    if (x > 0) cmd.append(x, 'v');
                    else if (x < 0) cmd.append(-x, '^');
                    if (y > 0) cmd.append(y, '>');
                    else if (y < 0) cmd.append(-y, '<');
                    cmd.append(1, 'A');
                    cmds_temp.insert(cmd);
                }
            }
            mid_point = pii{p.ff, m_nk[button].ss};
            if (mid_point != m_nk['X']) {
                for (string cmd : cmds_out_individual) {
                    if (y > 0) cmd.append(y, '>');
                    else if (y < 0) cmd.append(-y, '<');
                    if (x > 0) cmd.append(x, 'v');
                    else if (x < 0) cmd.append(-x, '^');
                    cmd.append(1, 'A');
                    cmds_temp.insert(cmd);
                }
            }
            swap(cmds_out_individual, cmds_temp);
            p = m_dk[button];
        }

        for (string cmd : cmds_out_individual) cmds_out.insert(cmd);
    }

    // Get the minimum length
    ll min_size = cmds_out.begin()->size();
    for (string cmd : cmds_out) min_size = min(min_size, (ll)cmd.size());
    set<string> temp_cmds_out;
    for (string cmd : cmds_out)
        if (cmd.size() == min_size) temp_cmds_out.insert(cmd);
    cmds_out.clear();
    cmds_out.insert(*temp_cmds_out.begin());
    cmds_out.insert(*(--temp_cmds_out.end()));
    return cmds_out;
}

void read_input() {
    string line;
    pii p = s_dk;
    while (getline(cin, line)) cmds.push_back(line);
}

void solve() {
    set<string> ss;

    for (string cmd : cmds) {
        ss.clear();
        ss.insert(cmd);
        ss = get_cmd_num(ss);
#if PART1
        for (int i = 0; i < 2; i++) ss = get_cmd_dir(ss);
#else
        for (int i = 0; i < 3; i++) ss = get_cmd_dir(ss);
#endif  // PART1
        cmd.erase(cmd.end() - 1);

        ll min_size = ss.begin()->size();
        for (string s : ss) min_size = min((ll)s.size(), min_size);

        ans += min_size * stoll(cmd);
    }
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
