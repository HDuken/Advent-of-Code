/*
 *   Copyright (c) 2025 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

ll ans = 0;
stringstream ss;

struct Node {
    string s;
    vector<shared_ptr<Node>> v;
    Node(string s_) : s(s_) {};
};

shared_ptr<Node> out;
vector<shared_ptr<Node>> inputs;
map<string, ll> m;            // For memoization and avoiding loops
map<string, vector<ll>> m_2;  // For memoization and avoiding loops

shared_ptr<Node> get_ptr(string s) {
    for (auto v : inputs)
        if (v->s == s) return v;

    shared_ptr<Node> out = make_shared<Node>(s);
    inputs.push_back(out);
    return out;
}

void read_input() {
    string line;
    string s;
    while (getline(cin, line)) {
        ss.clear();
        ss.str(line);

        ss >> s;
        s.erase(s.end() - 1);
        shared_ptr<Node> parent = get_ptr(s);

        while (ss >> s) parent->v.push_back(get_ptr(s));
    }

    out = get_ptr("out");
}

ll dfs(const string &s_start, const string &s_end) {
    if (m.find(s_start) != m.end()) return m[s_start];

    if (s_start == s_end) {
        m[s_start] = 1;
        return 1;
    }

    ll out = 0;
    for (auto child : get_ptr(s_start)->v) out += dfs(child->s, s_end);
    m[s_start] = out;
    return out;
}

// At each node is a array of 4 values
// v[0] = no. paths going through both fft and dac
// v[1] = no. paths going through only fft
// v[2] = no. paths going through only dac
// v[3] = no. paths going through NO fft and NO dac
vector<ll> dfs_2(const string &s) {
    if (m_2.find(s) != m_2.end()) return m_2[s];

    vector<ll> v{0, 0, 0, 0};
    for (auto child : get_ptr(s)->v)
        for (int i = 0; i < 4; i++) v[i] = v[i] + dfs_2(child->s)[i];

    if (s == "dac") {
        v[0] = v[0] + v[1];
        v[1] = 0;
        v[2] = v[2] + v[3];
        v[3] = 0;
    } else if (s == "fft") {
        v[0] = v[0] + v[2];
        v[1] = v[1] + v[3];
        v[2] = 0;
        v[3] = 0;
    }

    m_2[s] = v;
    return v;
}

void solve() {
#if PART1
    ans = dfs("you", "out");
#else
    m_2[out->s] = vector<ll>{0, 0, 0, 1};
    ans = dfs_2("svr")[0];

    // Re-use part 1 DFS, it works, but slower, have to reset the hash table
    // m.clear();
    // ll svr_dac = dfs("svr", "dac");
    // m.clear();
    // ll svr_fft = dfs("svr", "fft");
    // m.clear();
    // ll dac_fft = dfs("dac", "fft");
    // m.clear();
    // ll fft_out = dfs("fft", "out");
    // m.clear();
    // ll fft_dac = dfs("fft", "dac");
    // m.clear();
    // ll dac_out = dfs("dac", "out");
    // ans = svr_dac * dac_fft * fft_out + svr_fft * fft_dac * dac_out;
#endif  // PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
