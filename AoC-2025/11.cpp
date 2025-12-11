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

        while (ss >> s) {
            shared_ptr<Node> child = get_ptr(s);

            parent->v.push_back(child);
        }
    }

    out = get_ptr("out");
}

int dfs(shared_ptr<Node> n) {
    if (n == out) return 1;
    int out = 0;
    for (auto child : n->v) out += dfs(child);
    return out;
}

map<string, vector<ll>> m;  // For memoization and avoiding loops

// At each node is a array of 4 values
// v[0] = no. paths going through both fft and dac
// v[1] = no. paths going through only fft
// v[2] = no. paths going through only dac
// v[3] = no. paths going through NO fft and NO dac
vector<ll> dfs_2(shared_ptr<Node> n) {
    if (m.find(n->s) != m.end()) return m[n->s];

    vector<ll> v{0, 0, 0, 0};
    for (auto child : n->v)
        for (int i = 0; i < 4; i++) v[i] = v[i] + dfs_2(child)[i];

    if (n->s == "dac") {
        v[0] = v[0] + v[1];
        v[1] = 0;
        v[2] = v[2] + v[3];
        v[3] = 0;
    } else if (n->s == "fft") {
        v[0] = v[0] + v[2];
        v[1] = v[1] + v[3];
        v[2] = 0;
        v[3] = 0;
    }

    m[n->s] = v;
    return v;
}

void solve() {
#if PART1
    ans = dfs(get_ptr("you"));
#else
    m[out->s] = vector<ll>{0, 0, 0, 1};
    ans = dfs_2(get_ptr("svr"))[0];
#endif  // PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
