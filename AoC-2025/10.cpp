/*
 *   Copyright (c) 2025 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"
#include <set>

typedef vector<bool> vb;
const int N = 10;
int ans = 0;
int n_row = 0, n_col = 0;
stringstream ss;

vb xt;               // Targeted state
vi v0;               // Initial voltages
vector<vb> buttons;  // Vector of switches
set<vb> visited;     // Set of unique visited states

// Convert string to vector of boolean. Eg:
//   [.##.] -> 0 1 1 0
// [.###.#] -> 0 1 1 1 0 1
void read_input_1(string s) {
    s.erase(s.begin());
    s.erase(s.end() - 1);
    xt.clear();
    for (char c : s) xt.push_back((c == '.') ? false : true);
}

// Convert string to vector of boolean, include in buttons vector.
// Eg: (0,2,3,4) -> 1 0 1 1 1
void read_input_2(string s) {
    s.erase(s.begin());
    s.erase(s.end() - 1);
    replace(all(s), ',', ' ');

    vb out(xt.size(), false);
    stringstream ss_temp(s);
    int id;
    while (ss_temp >> id) out[id] = true;

    buttons.push_back(out);
}

void read_input_3(string s) {
    v0.clear();

    s.erase(s.begin());
    s.erase(s.end() - 1);
    replace(all(s), ',', ' ');

    stringstream ss_temp(s);
    int id;
    while (ss_temp >> id) v0.push_back(id);
    return;
}

vb xor_vb(const vb &v1, const vb &v2) {
    vb out(v1.size(), false);
    for (int i = 0; i < v1.size(); i++) out[i] = v1[i] ^ v2[i];

    return out;
}

vi reduce_voltage(const vi &v1, const vb &v2) {
    vi out(v1);
    for (int i = 0; i < v1.size(); i++)
        if (v2[i]) out[i] = v1[i] - 1;
    return out;
}

void solve() {
    string line, s;
    while (getline(cin, line)) {
        ss.clear();
        ss.str(line);

        buttons.clear();
        visited.clear();

        while (ss >> s) {
            if (s[0] == '[') {
                read_input_1(s);
            } else if (s[0] == '(') {
                read_input_2(s);
            } else {
                read_input_3(s);
            }
        }

#if PART1
        vb x0(xt.size(), false);
        set<vb> current_states;

        visited.insert(x0);
        current_states.insert(x0);
        while (visited.find(xt) == visited.end()) {
            set<vb> current_states_new;
            for (vb state : current_states) {
                for (vb button : buttons) {
                    vb state_new = xor_vb(state, button);
                    current_states_new.insert(state_new);
                    visited.insert(state_new);
                }
            }
            current_states = current_states_new;
            ans++;
        }
#else
        // Interger Linear Programming
#endif  // PART1
    }
}

int main(int argc, char const *argv[]) {
    solve();
    LOG(ans);
    return 0;
}

// 18335 too low
